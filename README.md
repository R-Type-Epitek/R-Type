<h1 align="center">🚀 RType EPITECH 🚀</h1>

<img src="https://github.com/R-Type-Epitek/R-Type/docs/assets/rtype.png" alt="RType Game" width="100%">

## 📖 About the Project

This RType project, developed by a dedicated team of five at EPITECH, is an exciting endeavor to recreate the classic
RType game. Our project not only aims to bring this beloved shooter game to life but also incorporates our unique twist
by implementing a custom Entity Component System (ECS). This approach allows for more dynamic and efficient game entity
management, providing an enhanced gaming experience.

RType is a side-scrolling space shooter game where players navigate a spacecraft through various levels, battling
enemies and avoiding obstacles. Our version preserves the essence of the original game while integrating modern
programming practices and graphical enhancements.

<br>

## 📚 Table of Contents

- [📖 About the Project](#-about-the-project)
- [📚 Table of Contents](#-table-of-contents)
- [🚀 Game Description](#-game-description)
- [🔧 Technologies](#-technologies)
- [📋 Prerequisites](#-prerequisites)
  - [Optional Dependencies](#optional-dependencies)
- [🛠️ Installation](#️-installation)
- [🚀 Usage](#-usage)
  - [Launch the server](#launch-the-server)
  - [Launch the client(s)](#launch-the-clients)
- [🤖 Entity Component System](#-entity-component-system)
- [😎 Contributors](#-contributors)
- [🤝 Contributing](#-contributing)
- [📜 License](#-license)
- [✨ Conclusion](#-conclusion)

<br>

## 🚀 Game Description

The RType game we're recreating involves a series of challenging levels where players control a spaceship to defeat
enemies and dodge obstacles. Each level offers unique challenges and requires players to adapt their strategies. The
game's fast-paced nature and retro charm make it an engaging experience for both new and seasoned players.

<br>

## 🔧 Technologies

This project uses several modern technologies, including:

C++: Our primary programming language, known for its efficiency and control over system resources.
CMake: A cross-platform tool that simplifies the build process.
Justfile: An intuitive, language-agnostic task runner.
Docker: Used for containerizing the application, ensuring consistent environments across different systems.
Doxygen: A documentation generator that helps us maintain clear and comprehensive code documentation.

<br>

## 📋 Prerequisites

Before starting, make sure to have the following installed:

- Justfile
- C++ Compiler
- CMake

### Optional Dependencies

- Doxygen: For generating project documentation.
- Docker: For running the game in a containerized environment.

<br>

## 🛠️ Installation

To launch the project, follow these steps:

1. ### Clone the repository:
   ```bash
   git clone git@github.com:R-Type-Epitek/R-Type.git
   ```

2. ### Navigate to the project directory:
   ```bash
   cd R-Type
   ```
3. ### Init the project:
    ```bash
      just
    ```
   OR
    ```bash
      just start
    ```

## 🚀 Usage

### Launch the server

```bash
./r-type_server
```

### Launch the client(s)

```bash
  ./r-type_client
```

## 🤖 Entity Component System

Our custom Entity Component System (ECS) is a core part of our game's architecture. It allows for a modular and flexible
approach to game object management. Entities represent objects in the game, components are data containers for various
attributes, and systems are logic processors that manipulate entities based on their components. This setup facilitates
a clean separation of concerns and makes the game easier to extend and maintain.

<br>

## 😎 Contributors

<div align="center">
    <table>
      <tr>
        <td align="center" style="min-width: 150px; border: 2px solid; padding: 20px;">
          <a href="https://github.com/raphaelCamblong">
            <img src="https://media.licdn.com/dms/image/D4E03AQGZQ9vaPPqEkQ/profile-displayphoto-shrink_800_800/0/1699623031673?e=2147483647&v=beta&t=mS6wgHcTBqRMd9DS-6mO3ZSjZEXVEt-QYT12jvSfT3w" width="150px;" alt="Raphaël CAMBLONG profile picture"/>
            <br />
            <b>Raphaël CAMBLONG</b>
          </a>
          <br />
          <div>
            <a href="https://github.com/R-Type-Epitek/R-Type/commits?author=raphaelCamblong" title="Code">👨‍💻</a>
            <a href="mailto:raphael.camblong@epitech.eu">✉️</a>
          </div>
        </td>
        <td align="center" style="min-width: 150px; border: 2px solid; padding: 20px">
          <a href="https://github.com/Koda777">
            <img src="https://media.licdn.com/dms/image/D4E03AQGVH4vm8X1cRw/profile-displayphoto-shrink_800_800/0/1699541667424?e=2147483647&v=beta&t=366VmIq2HQ-FCUuQd55qX_sASWGfecLitdMoqt_HV8E" width="150px;" alt="Alexandre DECOBERT profile picture"/>
            <br />
            <b>Alexandre DECOBERT</b>
          </a>
          <br />
          <div>
            <a href="https://github.com/R-Type-Epitek/R-Type/commits?author=Koda777" title="Code">👨‍💻</a>
            <a href="mailto:alexandre.decobert@epitech.eu">✉️</a>
          </div>
        </td>
        <td align="center" style="min-width: 150px; border: 2px solid; padding: 20px">
          <a href="https://github.com/EdouardPradie">
            <img src="https://media.licdn.com/dms/image/C4E03AQGkfVWmfbJVkA/profile-displayphoto-shrink_800_800/0/1651595290972?e=1710374400&v=beta&t=WOOMm8-lGck1mCcwDwm4mgLgG9fkZxOzsz4HEbfD820" width="150px;" alt="Edouard PRADIE profile picture"/>
            <br />
            <b>Edouard PRADIE</b>
          </a>
          <br />
          <div>
            <a href="https://github.com/R-Type-Epitek/R-Type/commits?author=EdouardPradie" title="Code">👨‍💻</a>
            <a href="mailto:edouard.pradie@epitech.eu">✉️</a>
          </div>
        </td>
      </tr>
      <tr>
        <td align="center" style="min-width: 150px; border: 2px solid; padding: 20px">
          <a href="https://github.com/sgLeopold">
            <img src="https://media.licdn.com/dms/image/D4E03AQFxIPuYk-j0kQ/profile-displayphoto-shrink_800_800/0/1683311154090?e=2147483647&v=beta&t=uRTIkH85zAq37wNP-cBtWY3k6plE09CuUGFKaL7ZPFk" width="150px;" alt="Léopold SALLAND GÉMARD profile picture"/>
            <br />
            <b>Léopold SALLAN G.</b>
          </a>
          <br />
          <div>
            <a href="https://github.com/R-Type-Epitek/R-Type/commits?author=sgLeopold" title="Code">👨‍💻</a>
            <a href="mailto:leopold.sallan-gemard@epitech.eu">✉️</a>
          </div>
        </td>
        <td align="center" style="min-width: 150px; border: 2px solid; padding: 20px">
          <a href="https://github.com/X-VINCENT">
            <img src="https://media.licdn.com/dms/image/C4D03AQERYR3cOO8fQg/profile-displayphoto-shrink_800_800/0/1646215295414?e=2147483647&v=beta&t=qk088hcnqNHZIxGEwcrA7DJomG90MouNBwzP3sGlmbg" width="150px;" alt="Xavier VINCENT profile picture"/>
            <br />
            <b>Xavier VINCENT</b>
          </a>
          <br />
          <div>
            <a href="https://github.com/R-Type-Epitek/R-Type/commits?author=X-VINCENT" title="Code">👨‍💻</a>
            <a href="mailto:pro.xv@outlook.fr">✉️</a>
          </div>
        </td>
      </tr>
    </table>
</div>

## 🤝 Contributing

We warmly welcome contributions! If you're interested in helping out, please read our contribution guidelines for more
information on how to get started.

<br>

## 📜 License

This project is licensed under the MIT License. Feel free to explore, modify, and distribute the code.

<br>

## ✨ Conclusion

We hope this documentation provides a comprehensive guide to our RType project. We're excited to see how players and
developers engage with our game. Thanks for your interest and support!