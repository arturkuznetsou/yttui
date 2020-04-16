# Controls:
 k: Go up
 j: Go down
 l: Open video

# How to run the program from the command line:
 -i <searchterm>: specifies the searchterm
 -o <format>: Specifies the command which will be ran when the key 'l' is pressed. %s will be replaced by the video ID.
  IE: '-o "firefox youtube.com/watch?v=%s' will result in the video being opened in firefox.
 -p: Makes the program look up the most popular uploads
 -l <lang>: sets the searching language. Uses ISO 639-1 codes. ( http://www.loc.gov/standards/iso639-2/php/code_list.php)\
 -h: Displays this
