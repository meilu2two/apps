#!/bin/sh

command=$1
echo "Command: $command"

case "$command" in
  boot) /usr/bin/screen -dmS my_app /home/meilu/git/apps/sh/screen_usage/endless_echo.sh
  ;;
  start) screen -dmS my_app ./endless_echo.sh
  ;;
  reattach) screen -rx my_app
  ;;
  quit) screen -X -S my_app quit
  ;;
  list) screen -ls
  ;;
  *) echo "default"
  ;;
esac
