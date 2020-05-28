from SimpleXMLRPCServer import SimpleXMLRPCServer
import xmlrpclib
import codecs
def wyswietl(n):
	print("Otrzymalem wiadomosc:")
	print(n)
	return 0

server = SimpleXMLRPCServer(("localhost", 5005))
server.register_function(wyswietl, "wyswietl")
server.serve_forever()
