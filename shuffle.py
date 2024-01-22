import pandas as pd

# Load the CSV file into a DataFrame
csv_file = './resources/nytcrossword.csv'
df = pd.read_csv(csv_file)

# Shuffle the rows
df_shuffled = df.sample(frac=1).reset_index(drop=True)

# Save the shuffled DataFrame back to the CSV file
shuffled_csv_file = './resources/nytcrossword.csv'
df_shuffled.to_csv(shuffled_csv_file, index=False)

print("Rows shuffled and saved to", shuffled_csv_file)
