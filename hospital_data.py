from tabulate import tabulate

# Patient Data
patients = [
    ["Rahul", "Delhi", 25, "9876543210", "Fever"],
    ["Mukesh", "Mumbai", 32, "9876543211", "Diabetes"],
    ["Rana", "Chennai", 45, "9876543212", "Hypertension"],
    ["Smitha", "Bangalore", 28, "9876543213", "Asthma"],
    ["Amol", "Pune", 30, "9876543214", "Cold"],
    ["Raj", "Kolkata", 40, "9876543215", "Flu"],
    ["Karan", "Hyderabad", 35, "9876543216", "Allergy"],
    ["Vinod", "Jaipur", 50, "9876543217", "Arthritis"],
    ["Ruhani", "Lucknow", 27, "9876543218", "Fever"],
    ["Sumit", "Ahmedabad", 33, "9876543219", "Migraine"],
    ["Lado", "Chandigarh", 22, "9876543220", "Anemia"],
    ["Suresh", "Bhopal", 55, "9876543221", "Diabetes"],
    ["Shubham", "Nagpur", 29, "9876543222", "Hypertension"],
    ["Rushikesh", "Indore", 38, "9876543223", "Cold"],
    ["Rajat", "Patna", 26, "9876543224", "Flu"]
]

# Headers
headers = ["Name", "Address", "Age", "Mobile Number", "Disease"]

# Displaying the table
print("\nPatient Data - Mahi Hospital\n")
print(tabulate(patients, headers=headers, tablefmt="grid"))
