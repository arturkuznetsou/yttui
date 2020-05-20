all: yttui

CFILES := cfiles/*
GOFILES := gofiles/gotoc.go gofiles/constid.go gofiles/errlog.go gofiles/login.go gofiles/settings.go gofiles/video.go
LINK := -lpthread -lncursesw
INSTALLDIR := /usr/local/bin/
CC := gcc




gotoc.h: $(GOFILES)
	go tool cgo -exportheader $@ $^

gotoc.a: $(GOFILES)
	go build -buildmode=c-archive $^

yttui: $(CFILES) gotoc.h gotoc.a
	$(CC) -o $@ $^ $(LINK)


clean: gotoc.a gotoc.h yttui
	rm -rf _obj gotoc.a gotoc.h

install: yttui
	mv $^ $(INSTALLDIR)
	cp help  /usr/local/etc/yttuihelp
