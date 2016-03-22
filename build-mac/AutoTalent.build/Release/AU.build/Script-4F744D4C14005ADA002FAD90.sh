#!/bin/sh
if [ -f "$HOME/Library/Application Support/AU Lab/com.apple.audio.aulab_componentcache.plist" ]
  then
	rm "$HOME/Library/Application Support/AU Lab/com.apple.audio.aulab_componentcache.plist"
fi

if [ -f "$HOME/Library/Caches/com.apple.audiounits.cache" ]
  then
	rm "$HOME/Library/Caches/com.apple.audiounits.cache"
fi
