package org.socialnetworklabseven.domain.validators;

import org.socialnetworklabseven.domain.User;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class UserValidator implements Validator<User> {
    @Override
    public void validate(User entity) throws ValidationException {
        String errors="";
        String emailRegex = "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$";
        Pattern pattern = Pattern.compile(emailRegex);
        Matcher matcher = pattern.matcher(entity.getId());
        if(!matcher.matches()){
            errors+=entity.getId()+" is not a valid email address";
        }
        if (entity.getFirstName() == null || entity.getFirstName().isEmpty()) {
            errors += "The first name of the user must not be null or empty!\n";
        }
        if (entity.getLastName() == null || entity.getLastName().isEmpty()) {
            errors += "The last name of the user must not be null or empty!\n";
        }
        if (!errors.isEmpty()) {
            throw new ValidationException(errors);
        }
    }
}
