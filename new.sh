id="$1"
title="$1"
folder="${title}"
complile="${folder}/main.cpp"

mkdir ./"${folder}"
cp -r ./template/* ./"${folder}"/
echo "add_executable(${id} ${complile})" >> CMakeLists.txt
