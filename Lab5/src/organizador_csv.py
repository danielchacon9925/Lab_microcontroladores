"""
# Abrir el archivo original
with open('punch.csv', 'r') as file:
    lines = file.readlines()

# Eliminar espacios adicionales alrededor de las comas y guardar las líneas actualizadas
updated_lines = [line.strip().replace(' ,', ', ') for line in lines]

# Escribir las líneas actualizadas en un nuevo archivo CSV
with open('datos_actualizados.csv', 'w') as file:
    for line in updated_lines:
        file.write(line + '\n')
"""

# Lista de nombres de archivos de entrada y salida
input_files = ['punch.csv', 'down.csv', 'up.csv']
output_files = ['punch.csv', 'down.csv', 'up.csv']

# Iterar sobre cada par de archivos de entrada y salida
for input_file, output_file in zip(input_files, output_files):
    # Abrir el archivo original
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # Eliminar espacios adicionales alrededor de las comas y guardar las líneas actualizadas
    updated_lines = [line.strip().replace(' ,', ', ') for line in lines]

    # Escribir las líneas actualizadas en un nuevo archivo CSV
    with open(output_file, 'w') as file:
        for line in updated_lines:
            file.write(line + '\n')
