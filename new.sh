id="$2"
title="$1$2"
folder="${title}"
complile="${folder}/main.cpp"

mkdir ./"${folder}"
cp -r ./template/* ./"${folder}"/
echo "add_executable(${id} ${complile})" >> CMakeLists.txt
