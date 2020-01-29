# php-hunspell-ext

This is a PHP module made in C++ to use the Hunspell library directly inside PHP.

Intead of using the Zend engine, was opted to use the [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP) library, which makes everything easier to work with development of PHP C++ extensions.

## Dependencies
---

Build dependencies:
```bash
g++ cmake make libphpcpp libhunspell
```

Runtime dependencies:
```bash
libphpcpp libhunspell
```

[PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP) and [Hunspell](https://github.com/hunspell/hunspell) libraries can be download from their repositories.

## Build & Installation
---

First it's need to build the extension, this can be done by running these commands below:

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
---

After installing the extension you can access the `FireworkWeb\HunspellExt` class.

```php
use FireworkWeb\HunspellExt;

// Construct a new instance with the path of dictionary "aff" and "dic" files
$hunspell = new HunspellExt("en_US.aff", "en_US.dic");

// Checks if a word is misspelled or not, if it is, 
// return a non-zero value
if(! $hunspell->check("Somethong")) {

    // Get wrong word suggestions from dictionary,
    // return an array of strings
    $suggestions = $hunspell->suggest("Somethong");
}
```

## CMake build options
---

It's is provided some options before building the extension that must be changed depending on you PHP version or operational system.

### Variables:
- INSTALL_INI - Decides if the installation steps will copy or not the .ini file inside INI_DIR. Defaults to ON.

- INI_DIR - Path of PHP modules .ini directory, this may change depending on your PHP version. Defaults to "/etc/php/7.0/mods-available".

These variables can be set while calling `cmake` at the building steps:

```bash
cmake .. -DINSTALL_INI=OFF

#or

cmake .. -DINI_DIR="/etc/php/7.2/mods-available"
```