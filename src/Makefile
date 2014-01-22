

PROG		= xenherder.cgi

all: $(PROG)

xenherder.cgi: Makefile xenherder-cgi.c
	gcc -o $(@) -lxenlight xenherder-cgi.c

install: $(PROG)
	cp xenherder.cgi /usr/local/www/xenherder/htdocs/xenherder.cgi
	chown root:root  /usr/local/www/xenherder/htdocs/xenherder.cgi
	chmod u+s        /usr/local/www/xenherder/htdocs/xenherder.cgi
	cp xenherder.css /usr/local/www/xenherder/htdocs/xenherder.css

clean:
	rm -f $(PROG)

