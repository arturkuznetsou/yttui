# Controls:<br/>
 j: Go down one line.<br/>
 k: Go up one line.<br/>
 h + SHIFT: Go to the previous page.<br/>
 l + SHIFT: Go to the next page.<br/>
 l: Open the current highlighted video.<br/>
 CTRL + D: Go down ten lines.<br/>
 CTRL + U: Go up ten lines.<br/>
 ESC: exit.<br/>
 <br/>
<br/>
# How to run the program from the command line:<br/>
 -i <searchterm>: specifies the searchterm<br/>
 -o <format>: Specifies the command which will be ran when the key 'l' is pressed. %s will be replaced by the video link.<br/>
  IE: '-o "firefox %s"' will result in the video being opened in firefox.<br/>
 -p: Makes the program look up the most popular uploads. Also does this when no searchterm is specified (When no -i option is specified).<br/>
 -l <lang>: sets the searching language. Uses ISO 639-1 codes. ( http://www.loc.gov/standards/iso639-2/php/code_list.php ) <br/>
 -d: Makes the program replace the %s in the <format> with the ID instead of the link.<br/>
 -h: Displays this<br/>
