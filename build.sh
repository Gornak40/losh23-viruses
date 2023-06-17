#!/usr/bin/bash
python3 -m venv venv && source venv/bin/activate && pip install -r requirements.txt && g++ val.cpp -O3 -march=native -o val && python3 battle.py solutions/ 01-01.txt
