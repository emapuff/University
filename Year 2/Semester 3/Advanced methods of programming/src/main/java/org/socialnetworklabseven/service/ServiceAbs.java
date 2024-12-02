package org.socialnetworklabseven.service;
import  org.socialnetworklabseven.domain.Entity;

public interface ServiceAbs<ID, E extends Entity<ID>> {
     Iterable<E> getEntities();
     void add(E entity);
}
