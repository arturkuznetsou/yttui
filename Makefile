all: yttui

CFILES := cfiles/*
GOFILES := gofiles/gotoc.go gofiles/constid.go gofiles/errlog.go gofiles/login.go gofiles/settings.go gofiles/video.go
LINK := -lpthread -lcurses
CC := gcc




gotoc.h: $(GOFILES)
	go tool cgo -exportheader $@ $^

gotoc.a: $(GOFILES)
	go build -buildmode=c-archive $^

yttui: $(CFILES) gotoc.h gotoc.a
	$(CC) -o $@ $^ $(LINK)
