#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von ParserTarget und TestParserTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestParser: ParserTarget TestParserTarget  
	g++ -g objs/Parser.o debug/TestParser.o -o debug/ParserTest
	

# compilieren des Files Parser.cpp zu Parser.o, 
# das Objekt-File ist abhängig von src/Parser.cpp und src/Parser.h
# flag:
# -c --> nur compilieren
# -g --> debug Informationen erzeugen
# -Wall --> alle meldungen erzeugen (Warning all)

ParserTarget :  src/Parser.cpp includes/Parser.h 
	g++ -g  -c -Wall src/Parser.cpp -o objs/Parser.o  


# TestParser.o ist abhängig von src/TestParser.cpp und src/Parser.h
TestParserTarget :  src/TestParser.cpp includes/Parser.h
	g++ -g  -c -Wall src/TestParser.cpp  -o debug/TestParser.o  



# loeschen aller files im verzeichnis obj und debug, dann neu erzeugen

cleanParser:
	rm -f objs/*.o
	rm -f debug/*
	$(MAKE) makeTestParser
	
	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
ParserOBJTarget:
	$(MAKE) ParserTarget

