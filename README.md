# Soft String Compare

C++ functions to judge the similarity of strings. Originally created to correct messy human input. Also compiles to WebAssembly.


## Install

You need `cmake` and a C++ compiler (such as `g++`) installed.

```bash
# clone repo
git clone https://github.com/Infinitifall/Soft-String-Compare
cd Soft-String-Compare

# make
cd build_native
cmake ../ -DCMAKE_BUILD_TYPE=Release
# cmake ../ -DCMAKE_BUILD_TYPE=Debug
cmake --build ./
```

## Use

The code in [example.cpp](./example.cpp) will try to correct the messy product names in [input_list.txt](data_dummy/input_list.txt) (see below) by matching them to a catalog of products.

```
iphne 13 pro maks
nkie ar jrdan 1
samsng 55" qled 4k smrt tv
dysin v11 absloote
instnt pot dou plus 6 qt
playstaton 5 digitl editon
fitbt versa 3 smrt wach
keurigk-cup coffe makr
bose quetcomfort 45 hdphnes
nutribullt pro - 13-pce hi-sped blndr
roomba i3+ evo self-emtying robt vacum
ninja foodie 10-in1 xl pro ar fyer & othr
lgo star wars milenim falcn

...
```

Run the `example` executable

```bash
# run
cd build_native
./example
```

```
✅ iPhone 13 Pro Max
✅ Nike Air Jordan 1
✅ Samsung 55" QLED 4K Smart TV
✅ Dyson V11 Absolute
✅ Instant Pot Duo Plus 6 Qt
✅ PlayStation 5 Digital Edition
✅ Fitbit Versa 3 Smartwatch
✅ Keurig K-Cup Coffee Maker
✅ Bose QuietComfort 45 Headphones
✅ NutriBullet Pro - 13-Piece High-Speed Blender
✅ iRobot Roomba i3+ EVO Self-Emptying Robot Vacuum
✅ Ninja Foodi 10-in-1 XL Pro Air Fryer & Other
✅ LEGO Star Wars Millennium Falcon
✅ Amazon Echo Dot (4th Gen) Smart Speaker
✅ VIZIO 5.1 Surround Sound Bar System
✅ Logitech MX Master 3S Wireless Mouse
✅ KitchenAid Artisan Series 5 Qt. Mixer
✅ GoPro HERO11 Black
✅ Apple Watch Series 7 GPS + Cellular
✅ Sonos One SL Wi-Fi Speaker
✅ Microsoft Surface Pro 8 Laptop
✅ LG 65" C1 Series OLED 4K UHD Smart TV
✅ Breville The Barista Express Espresso Machine
✅ Garmin Forerunner 945 GPS Running Watch
✅ Whirlpool 4.8 cu. ft. Front Load Washer
✅ Canon EOS R6 Mirrorless Camera
✅ Beats by Dr. Dre Studio3 Wireless Over-Ear Headphones
✅ Theragun Prime Deep Tissue Massage Gun
✅ Philips Norelco Multigroom All-in-One Trimmer
✅ Nespresso Vertuo Next Coffee & Espresso Maker
✅ Ring Video Doorbell Pro 2
✅ Brita Longlast Water Filter Pitcher
✅ Vitamix E310 Explorian Series Blender
✅ Traeger Pro 575 Wood Pellet Grill
✅ Oculus Quest 2 Advanced All-in-One Virtual Reality Headset
✅ Sunbeam Osmo 3 Reverse Osmosis Water Filter System
✅ Merax 10' Trampoline with Enclosure
✅ Klipsch HT-G700 3.1ch Dolby Atmos Soundbar
✅ YETI Tundra 45 Hard Cooler
✅ RTIC UltraLight 52 Qt Cooler
✅ HidrateSpark 3.0 32oz Insulated Water Bottle
❌ Bose QuietComfort 45 Headphones (lumin ultra-comfortble coper-infusd matres = Leesa Original Mattress)
✅ Anova Culinary Sous Vide Precision Cooker
✅ AeroGarden Harvest Elite Indoor Garden
✅ Waterpik Aquarius Water Flosser
✅ eufy RoboVac 11S (Slim) Robot Vacuum
✅ SKIL 1/4" Hex Electric Screwdriver
✅ SMOK Novo 4 Pod System Vape Kit
✅ Anker PowerCore 10000 Portable Charger

✅ count = 48
☑️  count = 0
❌ count = 1

🎯 ratio = 97.959 %
```

We see it is able to match severely misspelled product names to a very high degree (`>90%`).

We can also enter arbitrary strings to see how the system ranks items. For example, to see why `lumin ultra-comfortble coper-infusd matres` wasn't correctly matched:

```
Enter name: lumin ultra-comfortble coper-infusd matres
```

```
...

0.000 rating: Logitech MX Master 3S Wireless Mouse
0.000 rating: VIZIO 5.1 Surround Sound Bar System
0.360 rating: Vitamix E310 Explorian Series Blender
0.360 rating: NutriBullet Pro - 13-Piece High-Speed Blender
0.847 rating: Merax 10' Trampoline with Enclosure
0.847 rating: Philips Norelco Multigroom All-in-One Trimmer
2.357 rating: Anker PowerCore 10000 Portable Charger
2.659 rating: Nespresso Vertuo Next Coffee & Espresso Maker
3.701 rating: RTIC UltraLight 52 Qt Cooler
3.924 rating: Traeger Pro 575 Wood Pellet Grill
5.997 rating: Breville The Barista Express Espresso Machine
7.131 rating: Leesa Original Mattress
9.128 rating: Garmin Forerunner 945 GPS Running Watch
14.926 rating: Bose QuietComfort 45 Headphones

1: lumin ultra-comfortble coper-infusd matres
++ ____________comfort_______________________
++ ________________________________________es
++ _______________________co_________________
++ _____________________e ___________________
-- ___e __________________________
-- __________Co___________________
-- _____________________________es
-- __________Comfort______________
2: Bose QuietComfort 45 Headphones
```

We see that the correct choice `Leesa Original Mattress` is given the third highest rating. This is a particularly tricky example because it doesn't have much in common with the input string `lumin ultra-comfortble coper-infusd matres`.


## Performance

In [example.cpp](./example.cpp): In function `int main(int argc, char** argv)`: Comment out all lines except `real_run_wrapper(argc, argv);`. Compile with `Release` to enable optimization flags

```bash
# alternatively, run the `cmake release` task in VS Codium

cd build_native
cmake ../ -DCMAKE_BUILD_TYPE=Release
cmake --build ./
```

```bash
# using bash
time ./example ../data_dummy/all_list.txt ../data_dummy/input_list.txt ../data_dummy/output_list.txt ../data_dummy/all_list.txt
```

```bash
real    0m0.059s
user    0m0.052s
sys     0m0.003s
```

To correct 50 product names on a Dell XPS 15 (9510, 2021) equivalent.


## Compile to WebAssembly

You need a Wasm compiler (like `Emscripten`) and a local development server (such as `http-server`)

```bash
# make
cd build_wasm
emcmake cmake ../ -DCMAKE_BUILD_TYPE=Release
# emcmake cmake ../ -DCMAKE_BUILD_TYPE=Debug
emmake make


# run a local development server
npx http-server ./ -o -p 9999
# visit http://localhost:9999 in your web browser
```

Useful guides on C/C++ to Wasm:
- https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_Wasm
- https://marcoselvatici.github.io/WASM_tutorial/


## Programming in VS Codium

- `clangd` extension for completions, references, errors and hints
- `CodeLLDB` extension works great with the provided [launch.json](./.vscode/launch.json) and [tasks.json](./.vscode/tasks.json)
