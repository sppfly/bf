import random
import os

def generate_dna_sequence(length):
    """Generate a random DNA sequence of specified length."""
    bases = ['A', 'C', 'T', 'G']
    return ''.join(random.choice(bases) for _ in range(length))

def extract_subsequences(sequence, num_queries, min_length=10, max_length=30):
    """Extract random subsequences from the main sequence to use as queries."""
    queries = []
    seq_length = len(sequence)

    # Generate query lengths
    query_lengths = [random.randint(min_length, max_length) for _ in range(num_queries)]

    for length in query_lengths:
        # Choose a random starting position
        max_start = seq_length - length
        if max_start <= 0:
            # Sequence is shorter than query length, use the entire sequence
            start_pos = 0
            length = min(length, seq_length)
        else:
            start_pos = random.randint(0, max_start)

        query = sequence[start_pos:start_pos + length]
        queries.append({
            'sequence': query,
            'length': length,
            'original_start': start_pos,
            'original_file': None  # Will be filled later
        })

    return queries

def write_queries_to_file(queries, filename, source_filename):
    """Write query sequences to a file."""
    with open(filename, 'w') as f:
        f.write(f"# Query sequences extracted from {source_filename}\n")
        f.write(f"# Format: >Query [index] Length [length] OriginalPosition [position]\n")
        f.write(f"# Sequence: [DNA sequence]\n\n")

        for i, query in enumerate(queries):
            f.write(f">Query {i+1} Length {query['length']} OriginalPosition {query['original_start']}\n")
            f.write(f"{query['sequence']}\n\n")

    print(f"Generated {filename} with {len(queries)} queries")

def main():
    # Create output directories if they don't exist
    sequences_dir = "dna_sequences"
    queries_dir = "dna_queries"

    if not os.path.exists(sequences_dir):
        os.makedirs(sequences_dir)
    if not os.path.exists(queries_dir):
        os.makedirs(queries_dir)

    # Store all queries to create a master query file
    all_queries = []

    # Generate 10 DNA sequence files
    for i in range(1, 11):
        # Generate sequences of varying lengths between 100 and 1000 bases
        sequence_length = random.randint(100, 1000)
        sequence = generate_dna_sequence(sequence_length)

        # Generate queries from this sequence (3-6 queries per sequence)
        num_queries = random.randint(3, 6)
        queries = extract_subsequences(sequence, num_queries)

        # Mark which original file these queries came from
        for query in queries:
            query['original_file'] = f"dna_sequence_{i}.txt"

        all_queries.extend(queries)

        # Write sequence to file
        sequence_filename = f"{sequences_dir}/dna_sequence_{i}.txt"
        with open(sequence_filename, 'w') as f:
            f.write(f">DNA Sequence {i} - Length: {sequence_length} bases\n")
            # Write sequence in lines of 80 characters (standard FASTA format)
            for j in range(0, len(sequence), 80):
                f.write(sequence[j:j+80] + '\n')

        # Write queries for this sequence to a separate file
        query_filename = f"{queries_dir}/queries_from_sequence_{i}.txt"
        write_queries_to_file(queries, query_filename, f"dna_sequence_{i}.txt")

        print(f"Generated {sequence_filename} with {sequence_length} bases and {num_queries} queries")

    # Create a master file with all queries from all sequences
    master_query_file = f"{queries_dir}/all_queries.txt"
    write_queries_to_file(all_queries, master_query_file, "all sequences")

    # Create a summary file
    summary_file = f"{queries_dir}/summary.txt"
    with open(summary_file, 'w') as f:
        f.write("DNA Query Sequences Summary\n")
        f.write("=" * 30 + "\n\n")
        f.write(f"Total number of query files: 11\n")
        f.write(f"  - 10 individual query files (one per sequence)\n")
        f.write(f"  - 1 master file with all queries\n\n")
        f.write(f"Total number of queries: {len(all_queries)}\n\n")
        f.write("Files generated:\n")
        for i in range(1, 11):
            f.write(f"  - queries_from_sequence_{i}.txt: {sum(1 for q in all_queries if q['original_file'] == f'dna_sequence_{i}.txt')} queries\n")
        f.write(f"  - all_queries.txt: {len(all_queries)} queries\n")

    print(f"\nGenerated master query file: {master_query_file}")
    print(f"Total queries generated: {len(all_queries)}")
    print(f"Summary saved to: {summary_file}")

if __name__ == "__main__":
    main()
