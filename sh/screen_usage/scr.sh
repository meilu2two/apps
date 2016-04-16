#!/bin/sh

# lightweight all in one script to manage app in a screen session
app_name="endless_echo.sh"
session_name="my_app"
echo "Lightweight screen manager for $session_name"

#first command line argument is the command
command=$1
echo "Command: $command"

case "$command" in
  boot) /usr/bin/screen -dmS $session_name /home/meilu/git/apps/sh/screen_usage/$app_name
        # For automatic start at boot add a line like the following to rc.local
        # /bin/su - username -c "/absolute/path/to/this/script/name_of_this_script.sh boot"
  ;;
  start) screen -dmS $session_name ./$app_name
  ;;
  reattach) screen -rx $session_name
  ;;
  quit) screen -X -S $session_name quit
  ;;
  list) screen -ls
  ;;
  --help) echo "The following commands are provided:"
          echo "start    ... start $session_name in screen session"
          echo "reattach ... reattach screen session $session_name in multi display mode"
          echo "quit     ... quit screen session $session_name"
          echo "list     ... list all running screen sessions"
  ;;
  *) echo "unknown command: $command"
     echo "Try '$0 --help' for more information"
  ;;
esac
