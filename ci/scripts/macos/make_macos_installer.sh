#!/bin/bash

PROJECT_NAME=$1
VERSION=$2
CURRENT_DIRECTORY=$(pwd)
DMG_PATH=$CURRENT_DIRECTORY/$PROJECT_NAME.dmg
RESULT_DMG=$CURRENT_DIRECTORY/$PROJECT_NAME.$VERSION.dmg

echo "DMG path is $DMG_PATH"

rm -rf $RESULT_DMG
rm -rf $DMG_PATH.shadow
echo "Attach dmg..."
echo "hdiutil attach -owners on $DMG_PATH -shadow"
ATTACH_RESULT=$(hdiutil attach -owners on $DMG_PATH -shadow | tail -n 2)
ATTACH_DEV=$(echo $ATTACH_RESULT | awk '{print $1}')
ATTACH_PATH=$(echo $ATTACH_RESULT | awk '{print $5}')
echo "Attach dev is $ATTACH_DEV"
echo "Attach path is $ATTACH_PATH"
ln -s /Applications ${ATTACH_PATH}/Applications
cd $CURRENT_DIRECTORY
hdiutil detach $ATTACH_DEV
hdiutil convert -format UDZO -o $RESULT_DMG $DMG_PATH -shadow
rm -rf $DMG_PATH.shadow
exit 0
