package ro.mpp;

import java.util.List;
import java.util.Optional;

public interface CrudRepository<ID, T> {
    Optional<T> findById(ID id);

    List<T> findAll();

    T save(T entity);

    T update(T entity);

    void delete(ID id);
}
