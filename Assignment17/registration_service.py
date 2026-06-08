import re


# -----------------------------
# Custom Exceptions
# -----------------------------

class InvalidEmailError(ValueError):
    """
    Raised when the email format is invalid.
    """

    def __init__(self, email):
        super().__init__(
            f"Invalid email address provided: '{email}'"
        )


class UnderageError(Exception):
    """
    Raised when user age is below 18.
    """

    def __init__(self, age):
        super().__init__(
            f"User must be at least 18 years old. Provided age: {age}"
        )


# -----------------------------
# Registration Service
# -----------------------------

class RegistrationService:

    EMAIL_PATTERN = (
        r"^[a-zA-Z0-9._%+-]+"
        r"@[a-zA-Z0-9.-]+"
        r"\.[a-zA-Z]{2,}$"
    )

    def register_user(self, email: str, age: int) -> bool:

        # Internal invariant assertion
        assert isinstance(age, int), "Age must be an integer"

        # Validate email existence
        if email is None or email.strip() == "":
            raise InvalidEmailError(email)

        # Validate email format
        if not re.match(self.EMAIL_PATTERN, email):
            raise InvalidEmailError(email)

        # Validate age
        if age < 18:
            raise UnderageError(age)

        return True