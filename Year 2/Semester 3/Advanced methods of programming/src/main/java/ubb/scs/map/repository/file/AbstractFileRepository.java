package ubb.scs.map.repository.file;

import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.validators.Validator;
import ubb.scs.map.repository.memory.InMemoryRepository;

import java.io.*;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E>{
    private String filename;

    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        filename=fileName;
        loadData();
    }


    public abstract E createEntity(String line);
    public abstract String saveEntity(E entity);

    @Override
    public E save(E entity) {
        E e = super.save(entity);
        if (e == null)
            writeToFile();
        return e;
    }

    @Override
    public E findOne(ID id) {
        return super.findOne(id);
    }

    @Override
    public Iterable<E> findAll() {
        return super.findAll();
    }


    private void writeToFile() {

        try  ( BufferedWriter writer = new BufferedWriter(new FileWriter(filename))){

            for (E entity: entities.values()) {
                String ent = saveEntity(entity);
                writer.write(ent);
                writer.newLine();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        /*
            try { <- fara resurse

            }

            finally() <- se executa oricum
            daca facem cu resurse nu mai trebuie sa il inchidem noi
         */

    }

    private void loadData(){
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (!line.isEmpty()) {
                    E e = createEntity(line);
                    super.save(e);
                }
            }
        }
        catch (IOException e) { //fisierul nu exista
            throw new RuntimeException(e);
        }

    }

    @Override
    public E delete(ID id) {
        E deletedEntity = super.delete(id); // Use the inherited method from InMemoryRepository
        if (deletedEntity != null) {
            writeToFile(); // Update the file after deletion
        }
        return deletedEntity;
    }

    @Override
    public E update(E entity) {
        E updatedEntity = super.update(entity); // Use the inherited method from InMemoryRepository
        if (updatedEntity == null) {
            writeToFile(); // Update the file after the update
        }
        return updatedEntity;
    }
}
