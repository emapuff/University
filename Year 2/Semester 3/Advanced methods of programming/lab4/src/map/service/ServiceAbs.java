package map.service;
import map.domain.Friendship;
import map.domain.Tuple;
import map.domain.User;
import map.repository.Repository;
import map.domain.Entity;
import java.net.IDN;

public interface ServiceAbs<ID, E extends Entity<ID>> {
     Iterable<E> getEntities();
     void add(E entity);
}
