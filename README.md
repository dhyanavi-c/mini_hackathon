LifeLink – Blood Donor & Emergency Matching System

Team Name: SAD
Project Type: Mini-Hackathon Project
Programming Language: C

• Team Members

S. No.| Name| SAP ID
1| Stuti Bansriar| 590034463
2| Aarush Singh| 590033972
3| Dhyanavi Chhunchha| 590032746


 Project Overview

LifeLink is a menu-driven blood donor management and emergency blood request matching system developed entirely in the C programming language.

The project aims to make the process of finding potential blood donors simpler and more organized by maintaining donor information and emergency blood requests in a structured manner.

LifeLink allows users to register donors, submit emergency blood requests, and identify potential donors based on blood group, city, and availability.

The program uses file handling to store information permanently, ensuring that donor and request records remain available even after the program is closed.



 Problem Statement

During medical emergencies, finding suitable blood donors quickly can be challenging. Donor information may be scattered, outdated, or difficult to access.

LifeLink addresses this problem through a simple computerized system that organizes donor records and helps identify potential matches for emergency requests.


 Our Solution

LifeLink provides a basic blood donor management system with the following capabilities:

- Maintains a list of registered blood donors.
- Stores emergency blood requests.
- Searches for potential donors based on compatibility.
- Filters donors by city and availability.
- Preserves records using file handling.

The project demonstrates how fundamental C programming concepts can be applied to solve a meaningful real-world problem.


Features

1. Donor Registration
   Allows users to register donors by entering their details.

2. View Donors
   Displays the list of registered blood donors.

3. Blood Group Search
   Searches for donors belonging to a particular blood group.

4. City-Based Search
   Helps identify donors from a specific city.

5. Emergency Blood Requests
   Allows users to register emergency requests with patient details, blood group, city, units required, and urgency.

6. Compatible Donor Matching
   Identifies potential donors based on blood group compatibility, city, and availability.

7. Availability Management
   Allows donor availability status to be updated.

8. Permanent Data Storage
   Stores donor and request records in text files so that data is retained after program termination.

- Technologies Used

- Language: C
- Compiler: GCC / OnlineGDB C Compiler
- Storage: Text files
- Interface: Console-based menu system

No other programming language is used in the implementation.



 C Programming Concepts Used -

The project demonstrates the following concepts:

- Structures ("struct")
- Arrays
- Functions
- Conditional statements
- Loops
- String handling
- File handling ("fopen", "fscanf", "fprintf", "fclose")
- Searching and matching logic
- Menu-driven programming


 • How the Program Works

1. The program starts and loads previously saved donor and request records from text files.
2. The user interacts with the menu to select an operation.
3. Donor information or emergency requests can be entered and saved.
4. The matching function checks blood group compatibility.
5. Potential matches are filtered according to city and donor availability.
6. Updated records are stored in files for future use.


- Project Files

File| Description
"main.c"| Main C source code containing the program logic
"donors.txt"| Stores registered donor records
"requests.txt"| Stores emergency blood request records
"README.md"| Project documentation


• How to Compile and Run

Using GCC

1. Download or clone the repository.
2. Open a terminal in the project directory.
3. Compile the program:

gcc main.c -o lifelink

4. Run the program:

Windows: lifelink.exe

Linux / macOS: ./lifelink

The program will display a menu through which the user can access its features.


• Future Scope

The project can be improved in the future by adding:

- A graphical user interface
- Advanced donor search and filtering
- More detailed donor verification
- Notifications for emergency requests
- Integration with verified blood banks
- Improved record management

These features are proposed for future development and are not part of the current implementation.


⚠️ Disclaimer

LifeLink is an educational prototype developed for a mini-hackathon.

The donor matching system provides potential matches only. Actual blood donation and transfusion decisions must be made by qualified medical professionals after appropriate blood-group verification, screening, and crossmatching.


Our Vision

"A connection made in time can become a lifeline."

LifeLink aims to demonstrate how simple programming solutions can contribute to a more organized and responsive approach to emergency blood donor management.

Team SAD – LifeLink.
