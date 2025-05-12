
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.ArgumentCaptor;
import ro.mpp.Assigned;
import ro.mpp.AssignedRepository;
import ro.mpp.Observer;
import ro.mpp.Service;
import ro.mpp.User;
import ro.mpp.implementation.ServiceImpl;

import java.lang.reflect.Field;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;


class ServiceImplTest {

    private AssignedRepository assignedRepo;
    private ServiceImpl service;

    private User uploader;
    private Observer uploaderObs;
    private Observer otherObs;

    private Assigned stubAssignment;

    @BeforeEach
    void setUp() throws Exception {

        assignedRepo = mock(AssignedRepository.class);

        uploader = new User("u@u.com", "pass", "Uploader");
        setEntityId(uploader, 10);


        stubAssignment = new Assigned(uploader, null);
        setEntityId(stubAssignment, 99);


        service = new ServiceImpl(null, null, assignedRepo);
        uploaderObs = mock(Observer.class);
        otherObs  = mock(Observer.class);
        Map<String,Observer> map = new ConcurrentHashMap<>();
        map.put(uploader.getEmail(), uploaderObs);
        map.put("other@o.com", otherObs);

        Field f = ServiceImpl.class.getDeclaredField("loggedUsers");
        f.setAccessible(true);
        f.set(service, map);

        // 5) stub pentru findById în AssignedRepository
        when(assignedRepo.findById(99))
                .thenReturn(Optional.of(stubAssignment));
    }


    private void setEntityId(Object entity, int id) throws Exception {
        Field idField = entity.getClass().getSuperclass()
                .getDeclaredField("id");
        idField.setAccessible(true);
        idField.set(entity, id);
    }

    @Test
    void uploadFileForAssignment_persistsAndNotifiesOnlyOthers() throws Exception {

        service.uploadFileForAssignment(99, "path/to/file.txt");

        verify(assignedRepo).uploadFile(99, "path/to/file.txt");


        verify(uploaderObs, never()).assignmentUpdated(any());


        ArgumentCaptor<Assigned> captor = ArgumentCaptor.forClass(Assigned.class);
        verify(otherObs, times(1)).assignmentUpdated(captor.capture());

        Assigned sent = captor.getValue();
        assertSame(stubAssignment, sent, "Ar trebui să trimit exact același obiect recuperat");
    }
}
