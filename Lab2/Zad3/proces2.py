import xmlrpclib
import sys
import socket
import codecs

TCP_IP = '127.0.0.1'
TCP_PORT = 5000
BUFFER_SIZE = 20 

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

conn, addr = s.accept()
print 'Connection address:', addr

data = conn.recv(BUFFER_SIZE)
print "received data:", data
conn.close()

proxy = xmlrpclib.ServerProxy("http://localhost:5005/")
proxy.wyswietl(codecs.encode(data,"hex"))
