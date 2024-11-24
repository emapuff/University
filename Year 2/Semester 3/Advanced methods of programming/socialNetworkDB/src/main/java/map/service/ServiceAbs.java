package map.service;
import map.domain.Entity;

public interface ServiceAbs<ID, E extends Entity<ID>> {
     Iterable<E> getEntities();
     void add(E entity);
}
