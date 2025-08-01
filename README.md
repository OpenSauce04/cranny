# cranny

Command-line hourly music player

<img width="350" alt="Screenshot of Cranny running in the MacOS terminal" src="https://github.com/user-attachments/assets/29e43119-1da9-4b1f-9a06-637e7914658c" />

## What?

`cranny` is a simple music player which runs from the command line, with a twist.

Unlike typical music players, users pre-provide `cranny` with one or more sets of 24 music tracks, one for each hour of the day, and the track associated with the current hour of the day is played on loop until the time changes to the next hour.

This functionality is inspired by the music of the Animal Crossing series, where each hour of the day has a unique piece of music which plays depending on the current time.

Multiple of these track sets can be created in the form of playlists, and users can switch between these playlists on the fly.

## Where?

The currently known supported platforms are listed below.

Any platforms or architectures which aren't on this list have unknown support:

| Platform                         | Supported? |
|----------------------------------|------------|
| Linux (x86_64, ARM64)            | ✅         |
| MacOS (x86_64, ARM64)            | ✅         |
| Android (Termux) (x86_64, ARM64) | ✅         |
| FreeBSD (x86_64, ARM64)          | ✅         |
| Windows                          | ❌         |

Windows is notably absent from the list of supported operating systems. This is due to the program being written with Unix-like operating systems in mind, and adapting the code to work on Windows will take a bit of effort.

If someone contributes code of an acceptable quality which allows `cranny` to run on Windows, I will pull it, but otherwise Windows support is on a "whenever I get around to it" basis.

> [!NOTE]  
> All of the `cranny` binaries distributed in the [Releases](https://github.com/OpenSauce04/cranny/releases) section are statically linked **except** the Termux binaries.
>
> When downloading `cranny` for use on Termux, make sure you install the `libvorbis` package before running `cranny`:
> 
> ```
> pkg install libvorbis
> ```

## Why?

This piece of software was inspired by another music player named [Nook](https://github.com/mn6/nook-desktop). Unlike `cranny`, which can be used with any music, Nook was specifically designed for playing hourly Animal Crossing music.

For a long time I have made use of Nook, and I recently realized that its GitHub repository had become archived. The project had been unmaintained for a couple of years by that point, but the project being archived likely means that it is unlikely to ever receive more changes. This has two implications:

1. The Nook software relies on servers hosted by the author to download music. This means that if these servers were to go down, the software would no longer be usable, and as the author has clearly indicated that they have no interest in maintaining the project, this could happen at any time.
2. The project will no longer be updated to support newer platforms. Notably, Nook's official builds are only compiled for Intel Macs, running on Apple Silicon through the Rosetta 2 compatibility layer which is [scheduled for removal in 2027](https://www.macrumors.com/2025/06/10/apple-to-phase-out-rosetta-2/).

   Nook was also never supported Linux, unless you count the unofficial Flathub version which I breifly maintained while the upstream project was still receiving updates.

These two facts mean that Nook's days of usability are numbered. To address this, and also to spend time doing some recreational programming, I decided to write a psuedo-replacement.

## How?

Setting up `cranny` involves creating symlinks inside a `tracks` directory with pre-determined filenames.

Within the tracks directory, there will be one or more numbered directories, starting from `1`. These directories represent playlists, and each of them contains a complete set of tracks.

In each playlist, there are 24 tracks, each of which match up with a certain hour of the day, starting from `0` which corresponds to midnight:

```
~/.local/share/cranny/tracks/1/0
~/.local/share/cranny/tracks/1/1
~/.local/share/cranny/tracks/1/2

...

~/.local/share/cranny/tracks/1/21
~/.local/share/cranny/tracks/1/22
~/.local/share/cranny/tracks/1/23
```

To start, download the music you would like to use. `.wav`, `.ogg`, `.flac` and `.mp3` files are supported, but `.mp3` files are not recommended for music which is intended to be looped as the MP3 compression algorithm adds a small amount of silence to the start and end of tracks, stopping the loop from being seamless.

For users wishing to have a similar experience to Nook, loopable hourly themes from each game in the Animal Crossing series can be downloaded in `.ogg` format [from the Internet Archive](https://archive.org/details/animal-crossing-series-hourly-themes).

Once you've downloaded the music and put it in a place where you'd like to keep it, you can then begin creating the symlinks. First, create the tracks directory if it doesn't already exist, alongside the first playlist:

```
mkdir -p ~/.local/share/cranny/tracks/1/
```
Then, create a symlink for each hour from 0-23:
```
ln -sf ~/Music/Animal\ Crossing\ Series\ Hourly\ Themes/new-leaf-12am.ogg ~/.local/share/cranny/tracks/1/0
ln -sf ~/Music/Animal\ Crossing\ Series\ Hourly\ Themes/new-leaf-1am.ogg ~/.local/share/cranny/tracks/1/1
ln -sf ~/Music/Animal\ Crossing\ Series\ Hourly\ Themes/new-leaf-2am.ogg ~/.local/share/cranny/tracks/1/2

...

ln -sf ~/Music/Animal\ Crossing\ Series\ Hourly\ Themes/new-leaf-9pm.ogg ~/.local/share/cranny/tracks/1/21
ln -sf ~/Music/Animal\ Crossing\ Series\ Hourly\ Themes/new-leaf-10pm.ogg ~/.local/share/cranny/tracks/1/22
ln -sf ~/Music/Animal\ Crossing\ Series\ Hourly\ Themes/new-leaf-11pm.ogg ~/.local/share/cranny/tracks/1/23
```

Once this has been done, simply run the `cranny` command, and the music will begin playing.

When started, `cranny` will always initially play playlist `1`, but you can switch to a different playlist you have created using the `<` `>` keys.

## Build Instructions

The process of building `cranny` is simple:

Firstly, the libvorbis and libogg development packages must be installed. Package names will vary by platform, but on Debian and Ubuntu these packages are called `libogg-dev` and `libvorbis-dev`.

After these have been installed, simply run `make` from the project's root directory. There are three build options available:

- `make build-dynamic`

  This builds `cranny` with dynamically linked libraries, and is the default when just running `make` on its own.

- `make build-static`

  This builds `cranny` with statically linked libraries.

- `make build-debug`

  This builds `cranny` with debug information. Libraries are dynamically linked.

  The statically linked library files for libvorbis and libogg (*.a files) must be installed, and may be missing on certain platforms.

After `cranny` has finished building, it can be found at `./build/bin/<dynamic|static>/cranny`.
