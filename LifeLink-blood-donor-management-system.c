#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

#define DONOR_FILE "donors.txt"
#define REQUEST_FILE "requests.txt"

struct Donor {
    int id;
    char name[50];
    int age;
    char phone[15];
    char bloodGroup[5];
    char city[30];
    int available;
};

struct Request {
    int requestId;
    char patientName[50];
    char bloodGroup[5];
    char city[30];
    int units;
    char urgency[15];
};

struct Donor donors[MAX];
struct Request requests[MAX];

int donorCount = 0;
int requestCount = 0;

/* Compare strings without case sensitivity */
int sameText(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (tolower((unsigned char)a[i]) !=
            tolower((unsigned char)b[i])) {
            return 0;
        }
        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

/* Validate blood group */
int validBloodGroup(char bg[]) {
    char groups[8][5] = {
        "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
    };

    int i;

    for (i = 0; i < 8; i++) {
        if (sameText(bg, groups[i]))
            return 1;
    }

    return 0;
}

/* Simplified red-cell blood compatibility */
int isCompatible(char patient[], char donor[]) {

    if (sameText(patient, "O-"))
        return sameText(donor, "O-");

    if (sameText(patient, "O+"))
        return sameText(donor, "O-") ||
               sameText(donor, "O+");

    if (sameText(patient, "A-"))
        return sameText(donor, "O-") ||
               sameText(donor, "A-");

    if (sameText(patient, "A+"))
        return sameText(donor, "O-") ||
               sameText(donor, "O+") ||
               sameText(donor, "A-") ||
               sameText(donor, "A+");

    if (sameText(patient, "B-"))
        return sameText(donor, "O-") ||
               sameText(donor, "B-");

    if (sameText(patient, "B+"))
        return sameText(donor, "O-") ||
               sameText(donor, "O+") ||
               sameText(donor, "B-") ||
               sameText(donor, "B+");

    if (sameText(patient, "AB-"))
        return sameText(donor, "O-") ||
               sameText(donor, "A-") ||
               sameText(donor, "B-") ||
               sameText(donor, "AB-");

    if (sameText(patient, "AB+"))
        return validBloodGroup(donor);

    return 0;
}

/* Load donor records */
void loadDonors() {
    FILE *fp = fopen(DONOR_FILE, "r");

    donorCount = 0;

    if (fp == NULL)
        return;

    while (donorCount < MAX &&
           fscanf(fp, "%d %49s %d %14s %4s %29s %d",
                  &donors[donorCount].id,
                  donors[donorCount].name,
                  &donors[donorCount].age,
                  donors[donorCount].phone,
                  donors[donorCount].bloodGroup,
                  donors[donorCount].city,
                  &donors[donorCount].available) == 7) {

        donorCount++;
    }

    fclose(fp);
}

/* Load emergency requests */
void loadRequests() {
    FILE *fp = fopen(REQUEST_FILE, "r");

    requestCount = 0;

    if (fp == NULL)
        return;

    while (requestCount < MAX &&
           fscanf(fp, "%d %49s %4s %29s %d %14s",
                  &requests[requestCount].requestId,
                  requests[requestCount].patientName,
                  requests[requestCount].bloodGroup,
                  requests[requestCount].city,
                  &requests[requestCount].units,
                  requests[requestCount].urgency) == 6) {

        requestCount++;
    }

    fclose(fp);
}

/* Save a new donor */
int saveDonor(struct Donor d) {
    FILE *fp = fopen(DONOR_FILE, "a");

    if (fp == NULL)
        return 0;

    fprintf(fp, "%d %s %d %s %s %s %d\n",
            d.id, d.name, d.age, d.phone,
            d.bloodGroup, d.city, d.available);

    fclose(fp);
    return 1;
}

/* Save a new request */
int saveRequest(struct Request r) {
    FILE *fp = fopen(REQUEST_FILE, "a");

    if (fp == NULL)
        return 0;

    fprintf(fp, "%d %s %s %s %d %s\n",
            r.requestId, r.patientName,
            r.bloodGroup, r.city,
            r.units, r.urgency);

    fclose(fp);
    return 1;
}

/* Check duplicate donor ID */
int donorIDExists(int id) {
    int i;

    for (i = 0; i < donorCount; i++) {
        if (donors[i].id == id)
            return 1;
    }

    return 0;
}

/* Check duplicate request ID */
int requestIDExists(int id) {
    int i;

    for (i = 0; i < requestCount; i++) {
        if (requests[i].requestId == id)
            return 1;
    }

    return 0;
}

/* Register donor */
void registerDonor() {
    struct Donor d;

    if (donorCount >= MAX) {
        printf("Donor storage is full!\n");
        return;
    }

    printf("\n--- REGISTER BLOOD DONOR ---\n");

    printf("Enter donor ID: ");
    if (scanf("%d", &d.id) != 1) return;

    if (donorIDExists(d.id)) {
        printf("Donor ID already exists!\n");
        return;
    }

    printf("Enter name (one word): ");
    scanf("%49s", d.name);

    printf("Enter age: ");
    if (scanf("%d", &d.age) != 1) return;

    printf("Enter phone number: ");
    scanf("%14s", d.phone);

    printf("Enter blood group: ");
    scanf("%4s", d.bloodGroup);

    if (!validBloodGroup(d.bloodGroup)) {
        printf("Invalid blood group!\n");
        return;
    }

    printf("Enter city (one word): ");
    scanf("%29s", d.city);

    printf("Available? (1 = Yes, 0 = No): ");
    if (scanf("%d", &d.available) != 1) return;

    if (d.available != 0 && d.available != 1) {
        printf("Enter only 1 or 0!\n");
        return;
    }

    if (saveDonor(d)) {
        donors[donorCount] = d;
        donorCount++;
        printf("\nDonor registered successfully!\n");
    } else {
        printf("Could not save donor file!\n");
    }
}

/* Display all donors */
void viewDonors() {
    int i;

    printf("\n--- ALL REGISTERED DONORS ---\n");

    if (donorCount == 0) {
        printf("No donors registered.\n");
        return;
    }

    for (i = 0; i < donorCount; i++) {
        printf("\nID: %d\n", donors[i].id);
        printf("Name: %s\n", donors[i].name);
        printf("Age: %d\n", donors[i].age);
        printf("Phone: %s\n", donors[i].phone);
        printf("Blood Group: %s\n", donors[i].bloodGroup);
        printf("City: %s\n", donors[i].city);
        printf("Availability: %s\n",
               donors[i].available ? "Available" : "Unavailable");
    }
}

/* Search donors by blood group */
void searchBloodGroup() {
    char bg[5];
    int i, found = 0;

    printf("Enter blood group: ");
    scanf("%4s", bg);

    if (!validBloodGroup(bg)) {
        printf("Invalid blood group!\n");
        return;
    }

    printf("\n--- BLOOD GROUP SEARCH ---\n");

    for (i = 0; i < donorCount; i++) {
        if (sameText(bg, donors[i].bloodGroup) &&
            donors[i].available == 1) {

            printf("ID: %d | Name: %s | City: %s\n",
                   donors[i].id,
                   donors[i].name,
                   donors[i].city);

            found = 1;
        }
    }

    if (!found)
        printf("No available donors found.\n");
}

/* Search donors by city */
void searchCity() {
    char city[30];
    int i, found = 0;

    printf("Enter city: ");
    scanf("%29s", city);

    printf("\n--- CITY SEARCH ---\n");

    for (i = 0; i < donorCount; i++) {
        if (sameText(city, donors[i].city) &&
            donors[i].available == 1) {

            printf("ID: %d | Name: %s | Blood Group: %s\n",
                   donors[i].id,
                   donors[i].name,
                   donors[i].bloodGroup);

            found = 1;
        }
    }

    if (!found)
        printf("No available donors found.\n");
}

/* Register emergency request */
void registerRequest() {
    struct Request r;

    if (requestCount >= MAX) {
        printf("Request storage is full!\n");
        return;
    }

    printf("\n--- REGISTER EMERGENCY REQUEST ---\n");

    printf("Enter request ID: ");
    if (scanf("%d", &r.requestId) != 1) return;

    if (requestIDExists(r.requestId)) {
        printf("Request ID already exists!\n");
        return;
    }

    printf("Enter patient name (one word): ");
    scanf("%49s", r.patientName);

    printf("Enter required blood group: ");
    scanf("%4s", r.bloodGroup);

    if (!validBloodGroup(r.bloodGroup)) {
        printf("Invalid blood group!\n");
        return;
    }

    printf("Enter city (one word): ");
    scanf("%29s", r.city);

    printf("Enter units required: ");
    if (scanf("%d", &r.units) != 1) return;

    if (r.units <= 0) {
        printf("Units must be greater than zero!\n");
        return;
    }

    printf("Enter urgency (High/Medium/Low): ");
    scanf("%14s", r.urgency);

    if (saveRequest(r)) {
        requests[requestCount] = r;
        requestCount++;
        printf("\nEmergency request saved successfully!\n");
    } else {
        printf("Could not save request file!\n");
    }
}

/* Display all requests */
void viewRequests() {
    int i;

    printf("\n--- ALL EMERGENCY REQUESTS ---\n");

    if (requestCount == 0) {
        printf("No emergency requests found.\n");
        return;
    }

    for (i = 0; i < requestCount; i++) {
        printf("\nRequest ID: %d\n", requests[i].requestId);
        printf("Patient: %s\n", requests[i].patientName);
        printf("Blood Group: %s\n", requests[i].bloodGroup);
        printf("City: %s\n", requests[i].city);
        printf("Units: %d\n", requests[i].units);
        printf("Urgency: %s\n", requests[i].urgency);
    }
}

/* Find compatible donors */
void findCompatibleDonors() {
    int i, choice, found = 0;

    if (requestCount == 0) {
        printf("No emergency requests available!\n");
        return;
    }

    printf("\n--- SELECT A REQUEST ---\n");

    for (i = 0; i < requestCount; i++) {
        printf("%d. Request ID: %d | Patient: %s\n",
               i + 1,
               requests[i].requestId,
               requests[i].patientName);
    }

    printf("Select request number: ");

    if (scanf("%d", &choice) != 1)
        return;

    if (choice < 1 || choice > requestCount) {
        printf("Invalid selection!\n");
        return;
    }

    struct Request selected = requests[choice - 1];

    printf("\n--- POTENTIAL DONOR MATCHES ---\n");
    printf("Patient: %s\n", selected.patientName);
    printf("Required Group: %s\n", selected.bloodGroup);
    printf("Location: %s\n\n", selected.city);

    for (i = 0; i < donorCount; i++) {

        if (donors[i].available == 1 &&
            sameText(donors[i].city, selected.city) &&
            isCompatible(selected.bloodGroup,
                         donors[i].bloodGroup)) {

            printf("MATCH FOUND!\n");
            printf("Donor ID: %d\n", donors[i].id);
            printf("Name: %s\n", donors[i].name);
            printf("Blood Group: %s\n", donors[i].bloodGroup);
            printf("City: %s\n\n", donors[i].city);

            found = 1;
        }
    }

    if (!found)
        printf("No potential matches found.\n");

    printf("Professional blood-bank verification and "
           "crossmatching are essential.\n");
}

/* Rewrite donor file after availability changes */
int updateDonorFile() {
    FILE *fp = fopen(DONOR_FILE, "w");
    int i;

    if (fp == NULL)
        return 0;

    for (i = 0; i < donorCount; i++) {
        fprintf(fp, "%d %s %d %s %s %s %d\n",
                donors[i].id,
                donors[i].name,
                donors[i].age,
                donors[i].phone,
                donors[i].bloodGroup,
                donors[i].city,
                donors[i].available);
    }

    fclose(fp);
    return 1;
}

/* Update donor availability */
void updateAvailability() {
    int id, status, i;

    printf("Enter donor ID: ");

    if (scanf("%d", &id) != 1)
        return;

    for (i = 0; i < donorCount; i++) {

        if (donors[i].id == id) {

            printf("Enter new availability (1 = Yes, 0 = No): ");

            if (scanf("%d", &status) != 1)
                return;

            if (status != 0 && status != 1) {
                printf("Invalid availability!\n");
                return;
            }

            int oldStatus = donors[i].available;
            donors[i].available = status;

            if (updateDonorFile()) {
                printf("Availability updated successfully!\n");
            } else {
                donors[i].available = oldStatus;
                printf("Could not update donor file!\n");
            }

            return;
        }
    }

    printf("Donor ID not found!\n");
}

/* Main program */
int main() {
    int choice;

    loadDonors();
    loadRequests();

    printf("\n====================================\n");
    printf("       WELCOME TO LIFELINK\n");
    printf("====================================\n");

    printf("Donors loaded: %d\n", donorCount);
    printf("Requests loaded: %d\n", requestCount);

    do {
        printf("\n========== LIFELINK MENU ==========\n");
        printf("1. Register Blood Donor\n");
        printf("2. View All Donors\n");
        printf("3. Search Donors by Blood Group\n");
        printf("4. Search Donors by City\n");
        printf("5. Register Emergency Request\n");
        printf("6. View All Requests\n");
        printf("7. Find Compatible Donors\n");
        printf("8. Update Donor Availability\n");
        printf("9. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            return 0;
        }

        switch (choice) {
            case 1:
                registerDonor();
                break;

            case 2:
                viewDonors();
                break;

            case 3:
                searchBloodGroup();
                break;

            case 4:
                searchCity();
                break;

            case 5:
                registerRequest();
                break;

            case 6:
                viewRequests();
                break;

            case 7:
                findCompatibleDonors();
                break;

            case 8:
                updateAvailability();
                break;

            case 9:
                printf("\nThank you for using LifeLink!\n");
                break;

            default:
                printf("Invalid menu choice!\n");
        }

    } while (choice != 9);

    return 0;
}