# Project Detail

🎯 Raytracer Project

This project is a modular and extensible raytracer written in C++,
designed to render 3D scenes described in external configuration files.
The goal is to lay the foundation for a full-featured rendering engine,
supporting interface interaction, modularity, and advanced design practices.

🚀 Features

✅ Core Requirements

    Scene Configuration via external file (recommended: libconfig++)
    Image Display during and after generation
    Exit Handling during or after rendering
    Basic Scene Preview using a fast renderer
    Live Scene Reloading on file change
    Uses interfaces for lights and primitives to support extensibility
    Implements at least 2 design patterns (e.g., Factory, Builder, Decorator)

🛠 Architecture

    Clean modular structure allowing runtime extensibility
    Optional plugin system (./plugins/) for primitives, lights, and renderers

🖥 Libraries

    Only authorized:

        libconfig++ for scene parsing
        SFML for image display
        Standard C++ library



## Compilation :
    - make / make re
    - make clean / make fclean
    - make coding


## Coding Style :

    The Cpp code needs to ablige to a specified coding styke,
    to check if the code is complient with the norm execut
    the make coding command or the ./styleChecker.sh.
    To understand the errors and how to fix them please
    refers to the coding-cpp.txt.


## Documentation :

### Docusorus :
    To start the docusarus documentation :
    cd documentation/my-website
    npx docusaurus start

### Doxygen :
    The basic documentation fo the project is generated using the
    doxygen, to run the doxygen executable, please make sure you
    installed the pdf-latex librairie.
    To generate the PDF :
    ./generateDoc.sh


## Commit norm :

<Gitmoji> : [Element / Module] : [MESSAGE]

Gitmoji = The emoji approriate for the current modification.
[Element / Module] = The elemenet you applied the modification.
[MESSAGE] = A detail message of what you did.


Gitmojies:

    Code feature :
        - :sparkles: (✨): Introduce new features
        - :recycle: (♻️): Refactor / update code
        - :bug: (🐛): Fix a bug
        - :poop: (💩) : Remove Coding style or temporary fix
        - :rotating_light: (🚨) : Fix Compiling Warning
        - :fire: (🔥): Remove code or files

    Test feature :
        - :white_check_mark: (✅): Add, update, or pass tests

    Architecture :
        - :see_no_evil: (🙈): Add or update .gitignore files
        - :construction_worker: (👷): Add or update CI build system
        - :building_construction: (🏗️) : Make Architectural changes
        - :memo: (📝) : Add or update documentation

    ...
### Pull Request
    - :tada: (🎉): This Gitmoji must be used for each PR created!
    - :lipstick: (💄): This Gitmoji must be used for each PR merged!
    - :rewind: (⏪️): This Gitmoji must be used for each revert done!



## Git-Cli :

- Changer message de commit, avant qu'il soit push :
    ```bash
    git commit --amend -m "New commit message"
    ```

- Changer le message de commit, si il a deja été push :
    ```bash
    git commit --amend -m "New commit message"
    git push --force
    ```

- Un-add un ficher add par erreur qui est pas encore push:
    ```bash
    git restore --staged <file>
    ```

- Un-add un fichier qui a été commit :
    ```bash
    git reset --soft HEAD~1
    git restore --staged fichier-a-retirer.txt
    git commit -m "Nouveau message de commit (sans le fichier)"
    ```

## Note 

Grade : A médaille 
