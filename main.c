#include <stdio.h>
#include <string.h>

// Patient structure
typedef struct {
    int id;
    char name[50];
    int age;
    char ailment[50];
    char doctor[50];
    char status[20];
    char admissionDate[11];
    char dischargeDate[11];
} Patient;

// Dummy global data for billing
int patientIds[] = {1};
char admittedDates[][11] = {"2025-05-01"};
char dischargedDates[][11] = {""};
int treatmentPatientIds[] = {1};
char treatmentCosts[][10] = {"1500"};
int patientCount = 1;
int treatmentCount = 1;

// Function to update status
void update_status(char status[20]) {
    printf("\nUpdate patient status: ");
    scanf(" %[^\n]", status);
    printf("Updated status: %s\n", status);
}

// Function to search patients
int searchPatients(Patient patients[], int count, const char *key, const char *type) {
    int matchCount = 0;
    for (int i = 0; i < count; i++) {
        if ((strcmp(type, "name") == 0 && strstr(patients[i].name, key)) ||
            (strcmp(type, "ailment") == 0 && strstr(patients[i].ailment, key)) ||
            (strcmp(type, "doctor") == 0 && strstr(patients[i].doctor, key))) {

            printf("\n--- Match Found ---\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Ailment: %s\n", patients[i].ailment);
            printf("Doctor: %s\n", patients[i].doctor);
            printf("Status: %s\n", patients[i].status);
            matchCount++;
        }
    }
    return matchCount;
}

// Function to generate daily report
int generateDailyReport(Patient patients[], int count, const char *date) {
    int matchCount = 0;
    printf("\nDaily Report for: %s\n", date);
    for (int i = 0; i < count; i++) {
        if ((strcmp(patients[i].status, "admitted") == 0 && strcmp(patients[i].admissionDate, date) == 0) ||
            (strcmp(patients[i].status, "discharged") == 0 && strcmp(patients[i].dischargeDate, date) == 0)) {

            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Ailment: %s\n", patients[i].ailment);
            printf("Doctor: %s\n", patients[i].doctor);
            printf("Status: %s\n", patients[i].status);
            printf("\n");
            matchCount++;
        }
    }

    if (matchCount == 0) {
        printf("No patients admitted or discharged on this date.\n");
    }

    return matchCount;
}

// Billing System
int BillingSystem() {
    int id;
    printf("\nCalculate Bill for Patient ID: ");
    scanf("%d", &id);
    getchar(); // to consume newline after scanf

    for (int i = 0; i < patientCount; i++) {
        if (patientIds[i] == id) {
            char start[11], end[11];
            strcpy(start, admittedDates[i]);

            if (strlen(dischargedDates[i]) > 0)
                strcpy(end, dischargedDates[i]);
            else {
                printf("Enter today's date (YYYY-MM-DD): ");
                fgets(end, sizeof(end), stdin);
                end[strcspn(end, "\n")] = '\0';  // remove newline
            }

            int y1, m1, d1, y2, m2, d2;
            sscanf(start, "%d-%d-%d", &y1, &m1, &d1);
            sscanf(end, "%d-%d-%d", &y2, &m2, &d2);
            int days = d2 - d1 + 1;
            int roomCharge = days * 500;
            int totalTreatCost = 0;

            for (int j = 0; j < treatmentCount; j++) {
                if (treatmentPatientIds[j] == id) {
                    int cost = 0;
                    sscanf(treatmentCosts[j], "%d", &cost);
                    totalTreatCost += cost;
                }
            }

            printf("Days: %d\nRoom: %d\nTreatment: %d\nTotal: %d\n",
                   days, roomCharge, totalTreatCost, roomCharge + totalTreatCost);
            return 0;
        }
    }

    printf("Patient not found.\n");
    return 0;
}

// Main function
int main() {
    Patient patients[100];

    // Sample patient entry
    strcpy(patients[0].name, "John Doe");
    patients[0].id = 1;
    patients[0].age = 30;
    strcpy(patients[0].ailment, "Fever");
    strcpy(patients[0].doctor, "Dr. Smith");
    strcpy(patients[0].status, "admitted");
    strcpy(patients[0].admissionDate, "2025-05-01");
    strcpy(patients[0].dischargeDate, "");

    // Display info
    printf("--- Patient Info ---\n");
    printf("Name: %s\n", patients[0].name);
    printf("Age: %d\n", patients[0].age);
    printf("Ailment: %s\n", patients[0].ailment);
    printf("Doctor: %s\n", patients[0].doctor);
    printf("Status: %s\n", patients[0].status);

    // Update status
    update_status(patients[0].status);

    // Search by name
    printf("\n--- Search Result ---\n");
    searchPatients(patients, patientCount, "John", "name");

    // Daily report
    printf("\n--- Daily Report ---\n");
    generateDailyReport(patients, patientCount, "2025-05-01");

    // Billing
    BillingSystem();

    return 0;
}
