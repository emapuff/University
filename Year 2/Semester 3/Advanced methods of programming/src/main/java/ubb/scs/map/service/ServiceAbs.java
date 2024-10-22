package ubb.scs.map.service;
import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.User;
import ubb.scs.map.repository.Repository;
import ubb.scs.map.domain.Entity;
import java.net.IDN;

public interface ServiceAbs<ID, E extends Entity<ID>> {
     Iterable<E> getEntities();
     void add(E entity);

}
