from subprocess import Popen, PIPE
import os


popen1 = Popen(['./roma'], stdin=PIPE, stdout=PIPE, universal_newlines=True)
#popen2 = Popen(['./roma'], stdin=PIPE, stdout=PIPE)
#val = Popen(['./val'], stdin=PIPE, stdout=PIPE)
#val.stdin.write(bytes('1 2 3', 'ascii'))
