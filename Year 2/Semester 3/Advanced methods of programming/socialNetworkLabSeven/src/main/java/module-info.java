module org.socialnetworklabseven {
    requires javafx.controls;
    requires javafx.fxml;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    // Open the package containing your controller classes to javafx.fxml for reflection
    opens org.socialnetworklabseven to javafx.fxml;

    // Open the domain package to javafx.base for JavaFX to access User class
    opens org.socialnetworklabseven.domain to javafx.base;

    // Export the relevant packages
    exports org.socialnetworklabseven;
    exports org.socialnetworklabseven.domain;
}
