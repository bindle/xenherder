

PROG		= xenherder.cgi \
		  xenherder.min.js \
		  xenherder.min.css

all: $(PROG)
htdocs: xenherder.min.js xenherder.min.css

xenherder.min.js: Makefile xenherder.js jquery.min.js jquery.tablesorter.min.js
	@rm -f $(@)
	cat jquery.min.js >> $(@)
	cat jquery.tablesorter.min.js >> $(@)
	sed -e 's,//.*$$,,g' \
	   -e 's/^ *//g' \
	   -e 's/ *$$//g' \
	   -e 's,/\*.*\*/,,g' \
	   xenherder.js \
	   |grep -v '^$$' \
	   |sed -e ':a' -e 'N' -e '$$!ba' -e 's/\([{;]\)\n/\1/g' \
	   >> $(@)
	

xenherder.min.css: Makefile xenherder.css
	@rm -f $(@)
	sed -e 's,//.*$$,,g' \
	   -e 's/^[[:space:]]*//g' \
	   -e 's/[[:space:]]*$$//g' \
	   -e 's/:[[:space:]]*/:/g' \
	   -e 's/[[:space:]]\{2,\}/ /g' \
	   -e 's,/\*.*\*/,,g' \
	   xenherder.css \
	   |grep -v '^$$' \
	   |sed -e ':a' -e 'N' -e '$$!ba' -e 's/\([{;]\)\n/\1/g' \
	   >> $(@)
	

xenherder.cgi: Makefile xenherder-mockup.c
	gcc -o $(@) -lxenlight xenherder-mockup.c

install: $(PROG)
	cp xenherder.cgi     /usr/local/www/xenherder/htdocs/xenherder.cgi
	chown root:root      /usr/local/www/xenherder/htdocs/xenherder.cgi
	chmod u+s            /usr/local/www/xenherder/htdocs/xenherder.cgi
	cp xenherder.min.css /usr/local/www/xenherder/htdocs/xenherder.min.css
	cp xenherder.min.js  /usr/local/www/xenherder/htdocs/xenherder.min.js
	cp asc.gif           /usr/local/www/xenherder/htdocs/
	cp bg.gif            /usr/local/www/xenherder/htdocs/
	cp desc.gif          /usr/local/www/xenherder/htdocs/

clean:
	rm -f $(PROG)

