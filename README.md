# Prerequisites:<br/>
Configuring is done from the config.h. **You will need a YouTube API developer key** to use the program, which is not provided out of the box.<br/>
You will also need the Go dependencies on your machine. <br/>
```
     go get -u google.golang.org/api/youtube/v3
     go get -u golang.org/x/oauth2/...
```
<br/>
<br/>
## Default controls:<br/>
**When closing the terminal with yttui running, always first exist yttui. The browser will also be closed otherwise.**
 j: Go down one line.<br/>
 k: Go up one line.<br/>
 h + SHIFT: Go to the previous page.<br/>
 l + SHIFT: Go to the next page.<br/>
 l: Open the current highlighted video.<br/>
 CTRL + d: Go down ten lines.<br/>
 CTRL + u: Go up ten lines.<br/>
 ESC: exit.<br/>
 <br/>
<br/>
### How to run the program from the command line:<br/>
Usage:

yttui [OPTIONS...] [SEARCHSTRING]<br/>
<br/>
 -o (format): Specifies the command which will be ran when the key 'l' is pressed. %s will be replaced by the video link.<br/>
  IE: '-o "firefox %s"' will result in the video being opened in firefox.<br/>
 -p: Makes the program look up the most popular uploads. Also does this when no searchterm is specified (When no -i option is specified).<br/>
 -l (lang): sets the searching language. Uses ISO 639-1 codes. ( http://www.loc.gov/standards/iso639-2/php/code_list.php ) <br/>
 -d: Makes the program replace the %s in the (format) with the ID instead of the link.<br/>
 -h: Displays this<br/>
