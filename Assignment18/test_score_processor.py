import pytest

from score_processor import ScoreProcessor


# -----------------------------
# Shared Fixture
# -----------------------------

@pytest.fixture
def processor():
    return ScoreProcessor()


# -----------------------------
# Test Successful Processing
# -----------------------------

def test_successful_score_processing(
    tmp_path,
    processor
):
    """
    Test successful file reading
    and calculation.
    """

    # Create temporary test file
    test_file = tmp_path / "score.txt"

    test_file.write_text("7")

    result = processor.process_score_file(
        str(test_file)
    )

    assert result == 70


# -----------------------------
# Test Missing File
# -----------------------------

def test_missing_file(processor):
    """
    Test handling of missing file.
    """

    with pytest.raises(FileNotFoundError):

        processor.process_score_file(
            "missing_file.txt"
        )


# -----------------------------
# Test Invalid File Data
# -----------------------------

def test_invalid_data_format(
    tmp_path,
    processor
):
    """
    Test handling of invalid data.
    """

    # Create invalid file
    test_file = tmp_path / "invalid.txt"

    test_file.write_text("abc")

    with pytest.raises(ValueError):

        processor.process_score_file(
            str(test_file)
        )