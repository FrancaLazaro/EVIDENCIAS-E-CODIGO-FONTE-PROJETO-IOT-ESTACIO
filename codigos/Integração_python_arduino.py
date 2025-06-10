import serial
import json
from datetime import datetime

porta_serial = serial.Serial('COM5', 9600, timeout=1)

nome_arquivo = "medicoes.json"

try:
    with open(nome_arquivo, 'r') as f:
        medicoes = json.load(f)
except (FileNotFoundError, json.JSONDecodeError):
    medicoes = []

print("Lendo dados do Arduino...")

try:
    while True:
        linha = porta_serial.readline().decode('utf-8').strip()
        if linha:
            try:
                dado = json.loads(linha)
                dado["data_hora"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                medicoes.append(dado)
                print(dado)

                with open(nome_arquivo, 'w') as f:
                    json.dump(medicoes, f, indent=4)
            except json.JSONDecodeError:
                print("Linha inválida:", linha)
                
except KeyboardInterrupt:
    print("\nFinalizando...")
    porta_serial.close()
