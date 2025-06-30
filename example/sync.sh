#!/bin/bash
REMOTE_USER_HOST="xeno@192.168.1.101"
DEST_DIR="/home/xeno/codings/XenoControlDriver"

PROJECT_ROOT="/home/mf/codings/XenoControlDriver"
echo "Syncing '$PROJECT_ROOT' to '$REMOTE_USER_HOST:$DEST_DIR'..."
rsync -avz --delete --exclude-from="$PROJECT_ROOT/.gitignore" --exclude=".git" "$PROJECT_ROOT/" "$REMOTE_USER_HOST:$DEST_DIR"

echo "Sync finished."