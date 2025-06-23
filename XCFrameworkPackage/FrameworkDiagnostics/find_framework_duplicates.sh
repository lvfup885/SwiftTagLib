#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

BASE_DIR="$(cd "$(dirname "$0")/.." && pwd)"

XC1="$BASE_DIR/CxxTagLibBridge.xcframework"
XC2="$BASE_DIR/SwiftTagLib.xcframework"
XC3="$BASE_DIR/taglib.xcframework"

NAME1=$(basename "$XC1" .xcframework)
NAME2=$(basename "$XC2" .xcframework)
NAME3=$(basename "$XC3" .xcframework)

extract_symbols() {
  local path="$1"
  local name="$2"
  echo -e "${BLUE}Processing $name...${NC}"
  find "$path" -type f -perm +111 -exec nm -gU {} \; 2>/dev/null | awk '{if (NF > 2) print $3; else if (NF == 2) print $2;}' | sort -u
}

extract_symbols "$XC1" "$NAME1" > "${NAME1}_tmp.symbols.txt"
extract_symbols "$XC2" "$NAME2" > "${NAME2}_tmp.symbols.txt"
extract_symbols "$XC3" "$NAME3" > "${NAME3}_tmp.symbols.txt"

echo "Extracted $(wc -l < ${NAME1}_tmp.symbols.txt) symbols from $NAME1"
echo "Extracted $(wc -l < ${NAME2}_tmp.symbols.txt) symbols from $NAME2"
echo "Extracted $(wc -l < ${NAME3}_tmp.symbols.txt) symbols from $NAME3"

# Find all duplicates
cat "${NAME1}_tmp.symbols.txt" "${NAME2}_tmp.symbols.txt" "${NAME3}_tmp.symbols.txt" | sort | uniq -d > _duplicates_tmp.txt

if [[ ! -s _duplicates_tmp.txt ]]; then
  echo -e "${GREEN}No duplicates found between frameworks.${NC}"
  rm -f "${NAME1}_tmp.symbols.txt" "${NAME2}_tmp.symbols.txt" "${NAME3}_tmp.symbols.txt" _duplicates_tmp.txt
  exit 0
else
  echo -e "${RED}Duplicates found:${NC}"
  COUNT=$(wc -l < _duplicates_tmp.txt | xargs)
  echo "Total duplicates: $COUNT"
  # For each duplicate, check which frameworks contain it
  while read -r sym; do
    libs=""
    grep -Fxq "$sym" "${NAME1}_tmp.symbols.txt" && libs="$libs $NAME1"
    grep -Fxq "$sym" "${NAME2}_tmp.symbols.txt" && libs="$libs $NAME2"
    grep -Fxq "$sym" "${NAME3}_tmp.symbols.txt" && libs="$libs $NAME3"
    echo "$sym: [$libs ]"
  done < _duplicates_tmp.txt | head -n 20
  [[ $COUNT -gt 20 ]] && echo "...and $((COUNT-20)) more"
  mv "${NAME1}_tmp.symbols.txt" "${NAME1}.symbols.txt"
  mv "${NAME2}_tmp.symbols.txt" "${NAME2}.symbols.txt"
  mv "${NAME3}_tmp.symbols.txt" "${NAME3}.symbols.txt"
  mv _duplicates_tmp.txt duplicates.txt
fi