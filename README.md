# losh23-viruses

Если вы решили переиспользовать этот проект, будьте АККУРАТНЫ.

Здесь представлены две версии проекта.

Первая версия используется для проведения турнира каждый с каждым при помощи ```battle.py```. Она не пишет логи каждой игры, но почти дублирует вывод в консоль. По итогу получается json файл и файл логов. Если вы используете первую версию, вы можете запускать несколько процессов параллельно из одной папки.

Вторая версия используется для запуска единичной партии и отрисовки результата визуализотором. К тому же она умеет запускать сразу несколько игроков на одном поле.

```bash
g++ val2.cpp -O3 -march=native -o val2
python -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python gorill2.py engine1 engine2 val2 test.in
java -jar Visualizer2.jar log.txt 200
```
