# log_Manager

# Project Description


A lightweight console-based user management system developed in C that demonstrates fundamental file operations, structured logging, and CRUD functionality.

Perfect for learning C programming concepts including binary file I/O, enum types, struct usage, and modular program design.

# Features


Add Users - Create new users with ID, name, and role (Admin/User/Guest)

List Users - Display all registered users

Update Users - Modify existing user information

Delete Users - Remove users from the system

Logging System - Automatic logging of all operations with timestamps

Data Persistence - User data stored in binary file (users.dat)


# Project Structure


main.c          # Program entry point

operations.c    # Core user management operations

operations.h    # User structure and function declarations

logger.c        # Logging functionality

logger.h        # Log type definitions

users.dat       # Binary user data storage

system.log      # Operation logs

Makefile        # Build automation


# How It Works



The program provides a menu-driven interface with the following options: 


Add a new user - Enter ID, name, and assign a role

Show users list - Display all registered users

Update user information - Modify existing user data

Delete a user - Remove a user by ID

Exit - Press ENTER to quit


# Data Storage


User data is stored in binary format in users.dat

Each user record contains:

    ID (10 characters max)

    Name (32 characters max)

    Role (Admin/User/Guest)


# Logging System


All operations are logged to system.log with:



Timestamp [YYYY-MM-DD HH:MM:SS]

Operation type (INFO/WARN/ERROR)

Detailed operation message



Example log entries:

    [2026-03-05 12:30:59] User Added ID : 0192

    [2026-03-05 12:38:37] User Updated ID : 0192


# Building and Running


compile:

    gcc main.c operations.c logger.c -o user_management

run:

    ./user_management

compile and run at once (by makefile):

    make


# Requirements



C compiler (GCC recommended)

Standard C libraries

Terminal/Command Prompt



# Key Functions



user_add() - Add new user with duplicate ID checking

user_list() - Display all users with role mapping

user_update() - Modify existing user information

user_delete() - Remove user using temporary file method

logMessage() - Write timestamped log entries


# Use Cases



-Learning C file operations

-Understanding binary file I/O

-Practicing struct and enum usage

-Implementing logging mechanisms

-Building console-based CRUD applications


# Notes



User IDs must be unique


Input buffer is properly cleared to avoid issues

The system handles file errors gracefully

All operations are logged for audit purposes

Role selection uses enum values (1=Admin, 2=User, 3=Guest)


# Planned Features



I am continuing to develop the project! The following features are my next goals:



Password protection

Search functionality

GUI interface

Database integration

Advanced sorting/filtering



# License

This project is open source and available for educational purposes.