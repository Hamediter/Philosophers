#!/bin/bash

# Fichier de sortie
output_file="all_code.txt"

# Vide le fichier de sortie s'il existe déjà
> "$output_file"

# Concatène tous les fichiers .c et .h dans all_code.txt
cat *.c *.h >> "$output_file"

echo "Tous les fichiers .c et .h ont été concaténés dans $output_file"
