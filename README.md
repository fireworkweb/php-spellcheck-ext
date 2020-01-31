# php-spellcheck-ext

This is a PHP module made in C++ to use Spellchecking libraries directly inside PHP.

Intead of using the Zend engine directly, was opted to use the [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP) library, which makes everything easier to work with development of PHP C++ extensions.

## Dependencies

Required build dependencies:
```bash
g++ cmake make libphpcpp
```

Optional build dependencies (see [CMake build options](#cmake-build-options) for more information):
```bash
libhunspell-1.7 libvoikko
```

Required runtime dependencies:
```bash
libphpcpp
```

Optional runtime dependencies (see [CMake build options](#cmake-build-options) for more information):
```bash
libhunspell-1.7 libvoikko
```

[PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP), [Hunspell](https://github.com/hunspell/hunspell) and [Voikko](https://github.com/voikko/corevoikko) libraries can be downloaded from their repositories.

## Build & Installation

First it's needed to build the extension, this can be done by running these commands below:

```zsh
# inside php-hunspell-ext folder
mkdir build && cd build
cmake ..
make

# then you can install the extension by simply running:
sudo make install

# It's recommended that you enable the extesion by using phpenmod
sudo phpenmod hunspell-ext
```

## Usage


After installing the extension you can access the `FireworkWeb\Spellcheck\HunspellExt` and/or `FireworkWeb\Spellcheck\VoikkoExt` class.


### Hunspell extension

```php
use FireworkWeb\Spellcheck\HunspellExt;

// Construct a new instance with the path of dictionary "aff" and "dic" files
$hunspell = new HunspellExt("en_US.aff", "en_US.dic");

// Checks if a word is misspelled or not, if it is, 
// returns a non-zero value
if(! $hunspell->check("Somethong")) {

    // Get wrong word suggestions from dictionary,
    // returns an array of strings
    $suggestions = $hunspell->suggest("Somethong");
}
```

### Voikko (Finnish) extension

```php
use FireworkWeb\Spellcheck\VoikkoExt;

// Construct a new instance with language code and path to dictionary folder
$voikko = new VoikkoExt("fi_FI", "/path/to/dictionary/folder");

// Checks if a word is misspelled or not, if it is, 
// returns a non-zero value
if(! $voikko->check("Teskti")) {

    // Get wrong word suggestions from dictionary,
    // returns an array of strings
    $suggestions = $voikko->suggest("Teskti");
}
```

## CMake build options

It's is provided some options before building the extension that must be changed depending on you PHP version or operational system.

### Variables:
- `INSTALL_INI` - Decides if the installation steps will copy or not the `.ini` file inside `INI_DIR`. Defaults to ON.

- `INI_DIR` - Path of PHP modules .ini directory, this may change depending on your PHP version. Defaults to `"/etc/php/7.0/mods-available"`.

- `ENABLE_VOIKKO` - Decides if Voikko library will be used by the extension. Defaults to OFF.

- `ENABLE_HUNSPELL` - Decides if Hunspell library will be used by the extension. Defaults to ON.

These variables can be set while calling `cmake` at the building steps:

```bash
cmake .. -DINSTALL_INI=OFF

###

cmake .. -DINI_DIR="/etc/php/7.2/mods-available"

###

cmake .. -DENABLE_VOIKKO=ON -DENABLE_HUNSPELL=OFF
```