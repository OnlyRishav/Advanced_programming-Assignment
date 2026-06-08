import pytest

from registration_service import (
    RegistrationService,
    InvalidEmailError,
    UnderageError
)


# -----------------------------
# Shared Fixture
# -----------------------------

@pytest.fixture
def registration_service():
    return RegistrationService()


# -----------------------------
# Test Cases
# -----------------------------

def test_successful_registration(registration_service):

    result = registration_service.register_user(
        "john.doe@example.com",
        25
    )

    assert result is True


def test_invalid_email_format(registration_service):

    with pytest.raises(InvalidEmailError):

        registration_service.register_user(
            "invalid-email",
            22
        )


def test_empty_email(registration_service):

    with pytest.raises(InvalidEmailError):

        registration_service.register_user(
            "",
            22
        )


def test_none_email(registration_service):

    with pytest.raises(InvalidEmailError):

        registration_service.register_user(
            None,
            22
        )


def test_underage_user(registration_service):

    with pytest.raises(UnderageError):

        registration_service.register_user(
            "student@example.com",
            16
        )


def test_age_assertion(registration_service):

    with pytest.raises(AssertionError):

        registration_service.register_user(
            "user@example.com",
            "twenty"
        )