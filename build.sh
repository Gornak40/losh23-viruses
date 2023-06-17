#!/usr/bin/bash
python3 -m venv venv && source venv/bin/activate && pip install -r requirements.txt && g++ val.cpp -O3 -march=native -o val && g++ val2.cpp -O3 -march=native -o val2 && python3 battle.py solutions/ 01-01.txt
