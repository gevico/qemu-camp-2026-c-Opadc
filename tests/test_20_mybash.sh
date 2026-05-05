#!/usr/bin/env bash
set -e

cd ../exercises/20_mybash

script_file="$(mktemp)"
trap 'rm -f "$script_file"' EXIT

cat > "$script_file" <<'EOF'
myfile mybash
myfile obj/mybash/main.o
mysed s/unix/linux/ "unix is opensource. unix is free os."
mytrans src/mytrans/text.txt
mywc src/mytrans/text.txt
EOF

./mybash "$script_file"
