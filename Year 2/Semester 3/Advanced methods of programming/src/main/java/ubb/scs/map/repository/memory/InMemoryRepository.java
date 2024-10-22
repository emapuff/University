package ubb.scs.map.repository.memory;


import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.domain.validators.Validator;
import ubb.scs.map.repository.Repository;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    private final Validator<E> validator;
    protected Map<ID,E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities= new HashMap<>();
    }

    @Override
    public E findOne(ID id) {
        if (id==null)
            throw new IllegalArgumentException("id must be not null");
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values(); //orice e colectie e si iterabil
    }

    @Override
    public E save(E entity) throws ValidationException {

        if(entity==null)
            throw new IllegalArgumentException("ENTITY CANNOT BE NULL");
        validator.validate(entity);
        if(entities.containsKey(entity.getId()))
            return entity;
        else{
            entities.put(entity.getId(),entity);
            return null;
            //nu vom mai returna null, ci un optional daca exista, altfel o cutie goala
        }


    }

    @Override
    public E delete(ID id) {
        if(id==null){
            throw new IllegalArgumentException("ID CANNOT BE NULL");
        }
        return entities.remove(id);
    }

    /**
     *
     * @param entity
     *          entity must not be null
     * @return null - if the entity is updated,
     *                otherwise  returns the entity  - (e.g id does not exist).
     * @throws IllegalArgumentException
     *             if the given entity is null.
     * @throws ValidationException
     *             if the entity is not valid.
     */
    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity must not be null!");
        }
        validator.validate(entity);
        if (entities.containsKey(entity.getId())) {
            entities.put(entity.getId(), entity);
            return entity;
        } else {
            return null;
        }
    }
}
