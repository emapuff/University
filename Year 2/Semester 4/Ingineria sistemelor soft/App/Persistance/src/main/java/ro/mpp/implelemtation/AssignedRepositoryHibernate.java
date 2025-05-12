package ro.mpp.implelemtation;


import org.hibernate.Session;
import org.hibernate.query.Query;
import ro.mpp.Assigned;
import ro.mpp.AssignedRepository;
import ro.mpp.Mission;
import ro.mpp.util.HibernateUtil;

import java.util.List;
import java.util.Optional;

public class AssignedRepositoryHibernate implements AssignedRepository {

    @Override
    public Optional<Assigned> findById(Integer id) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            return Optional.ofNullable(session.get(Assigned.class, id));
        }
    }

    @Override
    public List<Assigned> findAll() {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            return session.createQuery("from Assigned", Assigned.class).list();
        }
    }

    @Override
    public Assigned save(Assigned entity) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();
            session.persist(entity);
            session.getTransaction().commit();
            return entity;
        }
    }

    @Override
    public Assigned update(Assigned entity) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();
            session.merge(entity);
            session.getTransaction().commit();
            return entity;
        }
    }

    @Override
    public void delete(Integer id) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();
            Assigned assigned = session.get(Assigned.class, id);
            if (assigned != null) {
                session.remove(assigned);
            }
            session.getTransaction().commit();
        }
    }

    @Override
    public List<Mission> findMissionsByUserId(Integer userId) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            Query<Mission> query = session.createQuery(
                    "select a.mission from Assigned a where a.user.id = :userId", Mission.class);
            query.setParameter("userId", userId);
            return query.list();
        }
    }

    @Override
    public void uploadFile(Integer assignedId, String fileName) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();

            Assigned assigned = session.get(Assigned.class, assignedId);
            if (assigned != null) {
                assigned.setUploadFileName(fileName);
                assigned.getMission().setFinished(true);
                session.merge(assigned);
            }

            session.getTransaction().commit();
        }
    }

    @Override
    public void validateAssignment(Integer assignedId) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();
            Assigned assigned = session.get(Assigned.class, assignedId);
            if (assigned != null) {
                assigned.setValidated(true);
                session.merge(assigned);
            }
            session.getTransaction().commit();
        }
    }

    @Override
    public List<Assigned> findUnvalidatedAssignments() {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            Query<Assigned> query = session.createQuery(
                    "from Assigned where validated = false", Assigned.class);
            return query.list();
        }
    }

    @Override
    public List<Assigned> getAssignmentsForUser(Integer userId){
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            Query<Assigned> query = session.createQuery(
                    "from Assigned where mission=:userId", Assigned.class);
            return query.list();
        }
    }
}
