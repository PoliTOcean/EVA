#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define TEMP_SENSOR_ADDRESS 0x5c
#define TEMP_SENSOR_REG 0x1f
#define MAX_BUF 255
#define HIGH "1"
#define LOW "0"
#define OUT "out"
#define CONFIG_PATH "/etc/jfan_controller.conf"

enum config_keys{temp_threshold, pin_number};

enum config_keys parse_config_key(char* key){
    if(!strcmp(key, "TEMP_THRESHOLD"))
    	return temp_threshold;
    	
    if(!strcmp(key, "GPIO_PIN_NUMBER"))
    	return pin_number;
}

void read_config_file(float* temp_thredshold, int* gpio_pin_number){
    FILE* file_ptr;
    char key[MAX_BUF];
    int value;
    
    file_ptr = fopen(CONFIG_PATH, "r");
    if(file_ptr == NULL){
    	printf("ERROR: Failed to open config file\n");
    	exit(1);
    }
    
    while(fscanf(file_ptr, "%s %d", key, &value)>0){
    	enum config_keys tmp = parse_config_key(key);
    	switch(tmp){
    	    case temp_threshold:
    	    	*temp_thredshold = value;
    	    	break;
    	    	
    	    case pin_number:
    	    	*gpio_pin_number = value;
    	    	break;
    	    	
    	    default:
    	    	break;
    	}
    }
    
    fclose(file_ptr);
}

int main() {
    int temp_sensor_fd, gpio_fd, gpio_pin_number = -1;
    char i2c_buffer[2], gpio_str[MAX_BUF];
    float temperature, temp_threshold = -1;
    
    // Read the configuration file /etc/jfan_controller.conf
    read_config_file(&temp_threshold, &gpio_pin_number);
    
    if(gpio_pin_number == -1){
    	printf("ERROR: missing GPIO_PIN_NUMBER parameter in config file\n");
    	exit(1);
    }
    
    if(temp_threshold == -1){
    	printf("ERROR: missing TEMP_THRESHOLD parameter in config file\n");
    	exit(1);
    }
    
    // Initialize the I2C bus and open the temperature sensor device file
    temp_sensor_fd = open("/dev/i2c-1", O_RDWR);
    if (temp_sensor_fd < 0) {
        perror("Failed to open I2C device file");
        exit(1);
    }
    if (ioctl(temp_sensor_fd, I2C_SLAVE, TEMP_SENSOR_ADDRESS) < 0) {
        perror("Failed to set I2C slave address");
        exit(1);
    }
    
    // Open the GPIO device file and set the GPIO pin as an output
    gpio_fd = open("/sys/class/gpio/export", O_WRONLY);
    if (gpio_fd < 0) {
        perror("Failed to open GPIO export file");
        exit(1);
    }
    
    sprintf(gpio_str, "%d", gpio_pin_number);
    
    write(gpio_fd, gpio_str, 2);
    close(gpio_fd);
    sprintf(gpio_str, "/sys/class/gpio/gpio%d/direction", gpio_pin_number);
    gpio_fd = open(gpio_str, O_WRONLY);
    if (gpio_fd < 0) {
        perror("Failed to open GPIO direction file");
        exit(1);
    }
    write(gpio_fd, OUT, 3);
    close(gpio_fd);
    
    sprintf(gpio_str, "/sys/class/gpio/gpio%d/value", gpio_pin_number);
    
    while (1) {
        // Read the temperature from the sensor
        i2c_buffer[0] = TEMP_SENSOR_REG;
        if (write(temp_sensor_fd, i2c_buffer, 1) != 1) {
            perror("Failed to write to temperature sensor");
            exit(1);
        }
        if (read(temp_sensor_fd, i2c_buffer, 2) != 2) {
            perror("Failed to read from temperature sensor");
            exit(1);
        }
        temperature = ((i2c_buffer[0] << 8) | i2c_buffer[1]) / 256.0;
        
        // Check if the temperature is above the threshold
        if (temperature > temp_threshold) {
            // Set the GPIO pin to high
            gpio_fd = open(gpio_str, O_WRONLY);
            if (gpio_fd < 0) {
                perror("Failed to open GPIO value file");
                exit(1);
            }
            write(gpio_fd, HIGH, 1);
            close(gpio_fd);
        } else {
            // Set the GPIO pin to low
            gpio_fd = open(gpio_str, O_WRONLY);
            if (gpio_fd < 0) {
                perror("Failed to open GPIO value file");
                exit(1);
            }
            write(gpio_fd, LOW, 1);
            close(gpio_fd);
        }
        
        // Wait for 1 second before checking the temperature again
        sleep(1);
    }
    
    return 0;
}
