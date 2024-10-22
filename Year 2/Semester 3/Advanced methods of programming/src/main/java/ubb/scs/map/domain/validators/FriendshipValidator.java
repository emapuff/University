package ubb.scs.map.domain.validators;

import ubb.scs.map.domain.Friendship;

public class FriendshipValidator implements Validator<Friendship> {
    @Override
    public void validate(Friendship friendship) throws ValidationException {
        String errors = "";
        if (friendship.getU1() == null || friendship.getU2()  == null) {
            errors += "The ids of the users must not be null!\n";
        }
        if (friendship.getU1() .equals(friendship.getU2())) {
            errors += "The ids of the users must be different!\n";
        }
        if (!errors.isEmpty()) {
            throw new ValidationException(errors);
        }
    }
}
