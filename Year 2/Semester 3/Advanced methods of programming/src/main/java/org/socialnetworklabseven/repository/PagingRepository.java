package org.socialnetworklabseven.repository;

import org.socialnetworklabseven.domain.Entity;
import org.socialnetworklabseven.domain.pagining.Page;
import org.socialnetworklabseven.domain.pagining.Pageable;

public interface PagingRepository<ID , E extends Entity<ID>> extends Repository<ID, E> {
    Page<E> findAllOnPage(String email, Pageable pageable);
}
