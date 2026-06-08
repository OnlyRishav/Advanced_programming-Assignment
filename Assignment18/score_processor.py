class ScoreProcessor:

    def process_score_file(self, file_path: str) -> int:
        """
        Reads a numeric score from a file,
        multiplies it by 10,
        and returns the result.
        """

        try:
            with open(file_path, "r") as file:

                content = file.read().strip()

                # Convert content to integer
                score = int(content)

        except FileNotFoundError:

            print("Error: File not found.")
            raise

        except ValueError:

            print(
                "Error: Invalid data format. "
                "File must contain a number."
            )
            raise

        else:

            print("Data processed successfully")

            return score * 10

        finally:

            print("File cleanup completed")