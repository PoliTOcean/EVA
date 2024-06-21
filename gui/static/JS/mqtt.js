
const mqtt_c = mqtt.connect("mqtt://10.0.0.254:9000");


// ! [DEBUG]
// const mqtt_c = mqtt.connect("mqtt://127.0.0.1:8080");

mqtt_c.on("connect", () => {
    console.info("[MQTT] Ready");
    mqtt_c.subscribe("state_commands/");
    mqtt_c.subscribe("gui/");
});




mqtt_c.on('message', function (topic, message) {
    let text = message.toString()
    switch (topic) {
        case "state_commands/":
            handleTask(text);
            break;
        case "gui/":
            text = JSON.parse(text)
            console.log(text["tempExt"])
            updateStatusesROV({"PID": text["pidState"], "ARMED": text["armed"]});
            updateIMU({"YAW": text["yaw"], "ROLL": text["roll"], "PITCH": text["pitch"]});
            updateSensors(text);
    }
})

mqtt_c.on('error', (error) => {
  try {
    console.error('MQTT Error:', error);
  } catch (err) {
    console.error('Error in error handler:', err);
  }
});