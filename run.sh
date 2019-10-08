#!/bin/bash

virtualenv -p python3 .env && source .env/bin/activate && pip3 install -r requirements.txt

cp input.txt temp.txt

if python3 ilp_solve.py 2>&1 >/dev/null; then
touch output.txt
g++ -std=c++17 wiring_edges.cpp -o wiring_edges && timeout 10s ./wiring_edges<temp.txt>output.txt
rm temp.txt
rm wiring_edges
python3 -W ignore draw_graph.py

else
echo "Infesiable Quotient Matrix"
fi
