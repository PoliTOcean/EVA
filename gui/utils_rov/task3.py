import csv
import matplotlib.pyplot as plt
from io import BytesIO
import base64

def leggi_csv(raw_file):
    rec1 = []
    rec2 = []
    rec3 = []

    file = raw_file.stream.read().decode('utf-8').splitlines() 

    reader = csv.reader(file)

    # Salta gli headers
    next(reader)

    for i, row in enumerate(reader):
        # print(row[1:])
        if i == 0:
            rec1 = [int(elemento) for elemento in row[1:]]
        elif i == 1:
            rec2 = [int(elemento) for elemento in row[1:]]
        elif i == 2:
            rec3 = [int(elemento) for elemento in row[1:]]

        # print("rec1:", rec1)  # Stampa rec1
        # print("rec2:", rec2)  # Stampa rec2
        # print("rec3:", rec3)  # Stampa rec3

    return rec1, rec2, rec3

def crea_grafico(rec1, rec2, rec3):
    try:
        if (rec1 is None) or (rec2 is None) or (rec3 is None):
            print("Nessun dato da visualizzare.")
            return

        x = list(range(1, 16))  # Assumiamo che le colonne siano da 1 a 15

        plt.figure(figsize=(10, 6))

        plt.plot(x, rec1, marker='o', color='r', label=f'Receiver 1')
        plt.plot(x, rec2, marker='o', color='g', label=f'Receiver 2')
        plt.plot(x, rec3, marker='o', color='b', label=f'Receiver 3')

        plt.xlabel('Day')
        plt.ylabel('# of sturgeons')
        plt.title('Number of sturgeons detected at each receiver over time')
        plt.legend()
        plt.grid(True)
        buffer = BytesIO()
        plt.savefig(buffer, format='png')
        buffer.seek(0)
        base64_img = base64.b64encode(buffer.getvalue()).decode('utf-8')
        plt.close()
        return base64_img

    except Exception as e:
        print(f"Si è verificato un errore durante la creazione del grafico: {e}")

def trova_massimo(int, rec):
    max_sum = float('-inf')
    current_sum = 0
    start_index = 0
    end_index = 0

    for i in range(len(rec) - 4):  # Consideriamo solo sottovettori di dimensione 5
        current_sum = sum(rec[i:i+5])

        if current_sum > max_sum:
            max_sum = current_sum
            start_index = i
            end_index = i + 4

    print(f"Receiver {int}:")
    print(f"\tSottovettore di somma massima: {rec[start_index:end_index+1]}")
    print(f"\tIndici: da {start_index} a {end_index}")
    print(f"\tSomma massima: {max_sum}\n")